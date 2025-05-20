//
// Created by 18224 on 2025/5/16.
//

#pragma once

// NOTE These next few lines may be win32 specific, you may need to modify them to compile on other platform
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <limits>
#include <queue>
#include <vector>

#ifdef DEBUG
#define ASSERT assert    // RectTree uses ASSERT(condition)
#else
#define ASSERT(_x)
#endif

//
// RectTree.h
//

#define RT_TEMPLATE template <class DataType, class ElemType, int Dims, class ElemTypeReal, int TMaxNodes, int TMinNodes>
#define RT_QUAL     RectTree<DataType, ElemType, Dims, ElemTypeReal, TMaxNodes, TMinNodes>

#define RT_DONT_USE_MEMPOOLS     // This version does not contain a fixed memory allocator, fill in lines with EXAMPLE to implement one.
#define RT_USE_SPHERICAL_VOLUME  // Better split classification, may be slower on some systems

// Fwd decl
class RTFileStream;    // File I/O helper class, look below for implementation and notes.


/// \class RectTree
/// Implementation of RectTree, a multidimensional bounding rectangle tree.
/// Example usage: For a 3-dimensional tree use RectTree<Object*, float, 3> myTree;
///
/// This modified, templated C++ version by Greg Douglas at Auran (http://www.auran.com)
///
/// DataType Referenced data, should be int, void*, obj* etc. no larger than sizeof<void*> and simple type
/// ElemType Type of element such as int or float
/// Dims Number of dimensions such as 2 or 3
/// ElemTypeReal Type of element that allows fractional and large values such as float or double, for use in volume calcs
///
/// NOTES: Inserting and removing data requires the knowledge of its constant Minimal Bounding Rectangle.
///        This version uses new/delete for nodes, I recommend using a fixed size allocator for efficiency.
///        Instead of using a callback function for returned results, I recommend and efficient pre-sized, grow-only memory
///        array similar to MFC CArray or STL Vector for returning search query result.
///
template <class DataType, class ElemType, int Dims, class ElemTypeReal = ElemType, int TMaxNodes=8, int TMinNodes = TMaxNodes/2>
class RectTree
{
protected:
    struct Node; // Fwd decl.  Used by other internal structs and iterator

public:
    /// Minimal bounding rectangle (n-dimensional)
    struct Rect {
        ElemType m_min[Dims]; ///< Min dimensions of bounding box
        ElemType m_max[Dims]; ///< Max dimensions of bounding box
    };

    // These constant must be declared after Branch and before Node struct
    // Stuck up here for MSVC 6 compiler.  NSVC .NET 2003 is much happier.
    enum {
        MaxNodes = TMaxNodes,                       ///< Max elements in node
        MinNodes = TMinNodes                        ///< Min elements in node
    };

    struct Statistics {
        int maxDepth;
        int avgDepth;

        int maxNodeLoad;
        int avgNodeLoad;
        int totalItems;
    };

public:

    RectTree();
    virtual ~RectTree();

    /// 插入条目
    /// \param aMin 边界矩形的最小值
    /// \param aMax 边界矩形的最大值
    /// \param aDataId 数据的正标识。可能为零，但不允许为负数.
    void insert(const ElemType aMin[Dims], const ElemType aMax[Dims], const DataType& aDataId);

    /// 移除条目
    /// \param aMin 边界矩形的最小值
    /// \param aMax 边界矩形的最大值
    /// \param aDataId 数据的正标识。可能为零，但不允许为负数.
    /// \return  1 if record not found, 0 if success.
    bool remove(const ElemType aMin[Dims], const ElemType aMax[Dims], const DataType& aDataId);

    /// 在搜索矩形范围内查找所有内容
    /// \param aMin 搜索边界矩形的最小值
    /// \param aMax 搜索边界矩形的最大值
    /// \param aCallback 用于返回结果的回调函数。回调函数应返回 “true” 以继续搜索
    /// \return 返回找到的条目数量
    int search(const ElemType aMin[Dims], const ElemType aMax[Dims], std::function<bool(const DataType&)> aCallback) const;

    /// 在搜索矩形范围内查找所有内容
    /// \param aMin 搜索边界矩形的最小值
    /// \param aMax 搜索边界矩形的最大值
    /// \param aCallback 用于返回结果的回调函数。回调函数应返回 “true” 以继续搜索
    /// \param aFinished 如果搜索完成，则此项设置为 true；如果搜索被中断，则设置为 false
    /// \return 返回找到的条目数量
    int search(const ElemType aMin[Dims], const ElemType aMax[Dims],
               std::function<bool(const DataType&)> aCallback, bool& aFinished) const;

    template <class Visitor>
    int search(const ElemType aMin[Dims], const ElemType aMax[Dims], Visitor& aVisitor) const
    {
#ifdef _DEBUG
        for (int index = 0; index < Dims; ++index) {
            ASSERT(aMin[index] <= aMax[index]);
        }
#endif    // _DEBUG
        Rect rect;
        for (int axis = 0; axis < Dims; ++axis) {
            rect.m_min[axis] = aMin[axis];
            rect.m_max[axis] = aMax[axis];
        }

        // NOTE: May want to return search result another way, perhaps returning the number of found elements here.
        int cnt = 0;
        search(m_root, &rect, aVisitor, cnt);

        return cnt;
    }

    /// Calculate Statistics
    Statistics calcStats();

    /// Remove all entries from tree
    void removeAll();

    /// Count the data elements in this container.  This is slow as no internal counter is maintained.
    int count() const;

    /// Load tree contents from file
    bool load(const char* aFileName);

    /// Load tree contents from stream
    bool load(RTFileStream& a_stream) const;


    /// save tree contents to file
    bool save(const char* aFileName);

    /// save tree contents to stream
    bool save(RTFileStream& a_stream) const;

    /**
     * Gets an ordered vector of the nearest data elements to a specified point
     * @param aPoint coordinate to measure against
     * @param aTerminate Callback routine to check when we have gathered sufficient elements
     * @param aFilter Callback routine to remove specific elements from the query results
     * @param aSquaredDist Callback routine to measure the distance from the point to the data element
     * @return vector of matching elements and their distance to the point
     */
    std::vector<std::pair<ElemType, DataType>> nearestNeighbors(
            const ElemType aPoint[Dims],
            std::function<bool(const std::size_t aNumResults, const ElemType aMinDist)> aTerminate,
            std::function<bool(const DataType aElement)> aFilter,
            std::function<ElemType(const ElemType a_point[Dims], const DataType a_data)> aSquaredDist) const;

public:
    /// Iterator is not remove safe.
    class Iterator
    {
    private:
        enum {
            MAX_STACK = 32
        }; // Max stack size. Allows almost n^32 where n is number of branches in node

        struct StackElement {
            Node* m_node;
            int   m_branchIndex;
        };

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef DataType                  value_type;
        typedef ptrdiff_t                 difference_type;
        typedef DataType*                 pointer;
        typedef DataType&                 reference;

    public:
        Iterator() : m_stack({}), m_tos(0)
        {
            for (int i = 0; i < Dims; ++i) {
                m_rect.m_min[i] = std::numeric_limits<ElemType>::min();
                m_rect.m_max[i] = std::numeric_limits<ElemType>::max();
            }
        }

        Iterator(const Rect& aRect) : m_stack({}), m_tos(0), m_rect(aRect)
        {
        }

        ~Iterator()
        {
        }

        /// Is iterator pointing to valid data
        constexpr bool IsNotNull() const
        {
            return m_tos > 0;
        }

        /// Access the current data element. Caller must be sure iterator is not nullptr first.
        DataType& operator*()
        {
            ASSERT(IsNotNull());
            StackElement& curTos = m_stack[m_tos - 1];
            return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
        }

        /// Access the current data element. Caller must be sure iterator is not nullptr first.
        const DataType& operator*() const
        {
            ASSERT(IsNotNull());
            StackElement& curTos = m_stack[m_tos - 1];
            return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
        }

        DataType* operator->()
        {
            ASSERT(IsNotNull());
            StackElement& curTos = m_stack[m_tos - 1];
            return &(curTos.m_node->m_branch[curTos.m_branchIndex].m_data);
        }

        /// Prefix ++ operator
        Iterator& operator++()
        {
            FindNextData();
            return *this;
        }

        /// Postfix ++ operator
        Iterator operator++(int)
        {
            Iterator retval = *this;
            FindNextData();
            return retval;
        }

        bool operator==(const Iterator& rhs) const
        {
            return ((m_tos <= 0 && rhs.m_tos <= 0) || 
                   (m_tos == rhs.m_tos && m_stack[m_tos].m_node == rhs.m_stack[m_tos].m_node && 
                    m_stack[m_tos].m_branchIndex == rhs.m_stack[m_tos].m_branchIndex));
        }

        bool operator!=(const Iterator& rhs) const
        {
            return ((m_tos > 0 || rhs.m_tos > 0) && 
                    (m_tos != rhs.m_tos || 
                     m_stack[m_tos].m_node != rhs.m_stack[m_tos].m_node || 
                     m_stack[m_tos].m_branchIndex != rhs.m_stack[m_tos].m_branchIndex));
        }

    private:
        /// Find the next data element in the tree (For internal use only)
        void FindNextData()
        {
            while (m_tos > 0) {
                StackElement curTos     = Pop();
                int          nextBranch = curTos.m_branchIndex + 1;

                if (curTos.m_node->IsLeaf()) {
                    // Keep walking through siblings until we find an overlapping leaf
                    for (int i = nextBranch; i < curTos.m_node->m_count; i++) {
                        if (RectTree::Overlap(&m_rect, &curTos.m_node->m_branch[i].m_rect)) {
                            Push(curTos.m_node, i);
                            return;
                        }
                    }
                    // No more data, so it will fall back to previous level
                } else {
                    // Look for an overlapping sibling that we can use as the fall-back node
                    // when we've iterated down the current branch
                    for (int i = nextBranch; i < curTos.m_node->m_count; i++) {
                        if (RectTree::Overlap(&m_rect, &curTos.m_node->m_branch[i].m_rect)) {
                            Push(curTos.m_node, i);
                            break;
                        }
                    }

                    Node* nextLevelnode = curTos.m_node->m_branch[curTos.m_branchIndex].m_child;

                    // Since cur node is not a leaf, push first of next level,
                    // zero-th branch to get deeper into the tree
                    Push(nextLevelnode, 0);

                    // If the branch is a leaf, and it overlaps, then break with the current data
                    // Otherwise, we allow it to seed our next iteration as it may have siblings that
                    // do overlap
                    if (nextLevelnode->IsLeaf() && RectTree::Overlap(&m_rect, &nextLevelnode->m_branch[0].m_rect)) {
                        return;
                    }
                }
            }
        }

        /// Push node and branch onto iteration stack (For internal use only)
        void Push(Node* aNode, int a_branchIndex)
        {
            m_stack[m_tos].m_node = aNode;
            m_stack[m_tos].m_branchIndex = a_branchIndex;
            ++m_tos;
            ASSERT(m_tos <= MAX_STACK);
        }

        /// Pop element off iteration stack (For internal use only)
        StackElement& Pop()
        {
            ASSERT(m_tos > 0);
            --m_tos;
            return m_stack[m_tos];
        }

        std::array<StackElement, MAX_STACK> m_stack; ///< Stack for iteration
        int                                 m_tos;   ///< Top Of Stack index
        Rect                                m_rect;  ///< Search rectangle

        friend class RectTree;
        // Allow hiding of non-public functions while allowing manipulation by logical owner
    };

    using iterator       = Iterator;
    using const_iterator = const Iterator;

    iterator begin(const Rect& aRect) const
    {
        iterator retval(aRect);

        if (!m_root->m_count) {
            return retval;
        }

        retval.Push(m_root, 0);

        // If the first leaf matches, return the root pointer, otherwise,
        // increment to the first match or empty if none.
        if (m_root->IsLeaf() && Overlap(&aRect, &m_root->m_branch[0].m_rect)) {
            return retval;
        }

        ++retval;
        return retval;
    }

    iterator begin() const
    {
        Rect full_rect;

        std::fill_n(full_rect.m_min, Dims, INT_MIN);
        std::fill_n(full_rect.m_max, Dims, INT_MAX);

        return begin(full_rect);
    }

    iterator end() const
    {
        iterator retval;
        return retval;
    }

    iterator end(const Rect& aRect) const
    {
        return end();
    }


protected:
    /// May be data or may be another subtree
    /// The parents level determines this.
    /// If the parents level is 0, then this is data
    struct Branch
    {
        Rect m_rect;                              ///< Bounds
        union {
            Node*       m_child;                    ///< Child node
            DataType    m_data;                     ///< Data Id or Ptr
        };
    };

    /// Node for each branch level
    struct Node {
        constexpr bool IsInternalNode() const { return m_level > 0; }   // Not a leaf, but a internal node
        constexpr bool IsLeaf()         const { return m_level == 0; }  // A leaf, contains data

        int     m_count;                ///< Count
        int     m_level;                ///< Leaf is zero, others positive
        Branch  m_branch[MaxNodes];     ///< Branch
    };

    /// A link list of nodes for reinsertion after a delete operation
    struct ListNode {
        ListNode*   m_next; ///< Next in list
        Node*       m_node; ///< Node
    };

    /// Variables for finding a split partition
    struct PartitionVars {
        int             m_partition[MaxNodes + 1];
        int             m_total;
        int             m_minFill;
        bool            m_taken[MaxNodes + 1];
        int             m_count[2];
        Rect            m_cover[2];
        ElemTypeReal    m_area[2];

        Branch          m_branchBuf[MaxNodes + 1];
        int             m_branchCount;
        Rect            m_coverSplit;
        ElemTypeReal    m_coverSplitArea;
    };

    /// Data structure used for Nearest Neighbor search implementation
    struct NNNode {
        Branch m_branch;
        ElemType minDist;
        bool isLeaf;

        inline bool operator<(const NNNode &other) const
        {
            return other.minDist < minDist; /// This is reversed on purpose to use std::priority_queue
        }
    };

    Node*           AllocNode() const;
    void            FreeNode(Node* aNode) const;
    void            InitNode(Node* aNode) const;
    void            InitRect(Rect* aRect) const;
    bool            InsertRectRec(const Rect* aRect, const DataType& aId, Node* aNode, Node** aNewNode, int aLevel) const;
    bool            InsertRect(const Rect* aRect, const DataType& aId, Node** aRoot, int aLevel) const;
    Rect            NodeCover(Node* aNode) const;
    bool            AddBranch(const Branch* aBranch, Node* aNode, Node** aNewNode) const;
    void            DisconnectBranch(Node* aNode, int aIndex) const;
    int             PickBranch(const Rect* aRect, Node* aNode) const;
    Rect            CombineRect(const Rect* aRectA, const Rect* aRectB) const;
    void            SplitNode(Node* aNode, const Branch* aBranch, Node** aNewNode) const;
    ElemTypeReal    RectSphericalVolume(const Rect* aRect) const;
    ElemTypeReal    RectVolume(const Rect* aRect) const;
    ElemTypeReal    CalcRectVolume(const Rect* aRect) const;
    void            GetBranches(Node* aNode, const Branch* aBranch, PartitionVars* aParVars) const;
    void            ChoosePartition(PartitionVars* aParVars, int aMinFill) const;
    void            LoadNodes(Node* a_nodeA, Node* aNodeB, PartitionVars* aParVars) const;
    void            InitParVars(PartitionVars* aParVars, int aMaxRects, int aMinFill) const;
    void            PickSeeds(PartitionVars* aParVars) const;
    void            Classify(int aIndex, int aGroup, PartitionVars* aParVars) const;
    bool            RemoveRect(const Rect* aRect, const DataType& aId, Node** aRoot) const;
    bool            RemoveRectRec(const Rect* aRect, const DataType& aId, Node* aNode, ListNode** aListNode) const;
    ListNode*       AllocListNode() const;
    void            FreeListNode(ListNode* aListNode) const;
    static bool     Overlap(const Rect* aRectA, const Rect* aRectB);
    void            ReInsert(Node* aNode, ListNode** aListNode) const;
    ElemType        MinDist(const ElemType a_point[Dims], const Rect& aRect) const;

    bool Search(const Node* aNode, const Rect* aRect, int& a_foundCount, std::function<bool(const DataType&)> aCallback) const;

    template <class Visitor>
    bool Search(const Node* aNode, const Rect* aRect, Visitor& aVisitor, int& a_foundCount) const
    {
        ASSERT(aNode);
        ASSERT(aNode->m_level >= 0);
        ASSERT(aRect);

        if (aNode->IsInternalNode()) { // This is an internal node in the tree
            for (int index = 0; index < aNode->m_count; ++index) {
                if (Overlap(aRect, &aNode->m_branch[index].m_rect)) {
                    if (!search(aNode->m_branch[index].m_child, aRect, aVisitor, a_foundCount)) {
                        return false; // Don't continue searching
                    }
                }
            }
        } else {// This is a leaf node
            for (int index = 0; index < aNode->m_count; ++index) {
                if (Overlap(aRect, &aNode->m_branch[index].m_rect)) {
                    const DataType& id = aNode->m_branch[index].m_data;

                    if (!aVisitor(id)) {
                        return false;
                    }
                    a_foundCount++;
                }
            }
        }

        return true; // Continue searching
    }

    void    RemoveAllRec(Node* aNode) const;
    void    Reset() const;
    void    CountRec(const Node* aNode, int& a_count) const;

    bool    SaveRec(const Node* aNode, RTFileStream& a_stream) const;
    bool    LoadRec(const Node* aNode, RTFileStream& a_stream) const;

    Node*        m_root;                ///< Root of tree
    ElemTypeReal m_unitSphereVolume;    ///< Unit sphere constant for required number of dimensions
};


// Because there is not stream support, this is a quick and dirty file I/O helper.
// Users will likely replace its usage with a Stream implementation from their favorite API.
class RTFileStream
{
    FILE* m_file;
public:
    RTFileStream()
    {
        m_file = nullptr;
    }

    ~RTFileStream()
    {
        Close();
    }

    bool OpenRead(const char* aFileName)
    {
        m_file = std::fopen(aFileName, "rb");
        return m_file != nullptr;
    }

    bool OpenWrite(const char* aFileName)
    {
        m_file = std::fopen(aFileName, "wb");
        return m_file != nullptr;
    }

    void Close()
    {
        if (m_file) {
            std::fclose(m_file);
            m_file = nullptr;
        }
    }

    template <typename TYPE>
    size_t Write(const TYPE& a_value)
    {
        ASSERT(m_file);
        return std::fwrite((void*) &a_value, sizeof(a_value), 1, m_file);
    }

    template <typename TYPE>
    size_t WriteArray(const TYPE* a_array, int a_count)
    {
        ASSERT(m_file);
        return std::fwrite((void*) a_array, sizeof(TYPE) * a_count, 1, m_file);
    }

    template <typename TYPE>
    size_t Read(TYPE& a_value)
    {
        ASSERT(m_file);
        return std::fread((void*) &a_value, sizeof(a_value), 1, m_file);
    }

    template <typename TYPE>
    size_t ReadArray(TYPE* a_array, int a_count)
    {
        ASSERT(m_file);
        return std::fread((void*) a_array, sizeof(TYPE) * a_count, 1, m_file);
    }
};


RT_TEMPLATE RT_QUAL::RectTree()
{
    ASSERT(MaxNodes > MinNodes);
    ASSERT(MinNodes > 0);


    // We only support machine word size simple data type eg. integer index or object pointer.
    // Since we are storing as union with non data branch
    ASSERT(sizeof(DataType) == sizeof(void*) || sizeof(DataType) == sizeof(int));

    // Precomputed volumes of the unit spheres for the first few dimensions
    const float UNIT_SPHERE_VOLUMES[] = {
            0.000000f, 2.000000f, 3.141593f,    // Dimension  0,1,2
            4.188790f, 4.934802f, 5.263789f,    // Dimension  3,4,5
            5.167713f, 4.724766f, 4.058712f,    // Dimension  6,7,8
            3.298509f, 2.550164f, 1.884104f,    // Dimension  9,10,11
            1.335263f, 0.910629f, 0.599265f,    // Dimension  12,13,14
            0.381443f, 0.235331f, 0.140981f,    // Dimension  15,16,17
            0.082146f, 0.046622f, 0.025807f,    // Dimension  18,19,20
        };

    m_root = AllocNode();
    m_root->m_level     = 0;
    m_unitSphereVolume  = (ElemTypeReal) UNIT_SPHERE_VOLUMES[Dims];
}

RT_TEMPLATE
RT_QUAL::~RectTree() {
    Reset(); // Free, or reset node memory
}

RT_TEMPLATE
void RT_QUAL::insert(const ElemType aMin[Dims], const ElemType aMax[Dims], const DataType& aDataId)
{
#ifdef _DEBUG
    for (int index = 0; index<Dims; ++index) {
        ASSERT(aMin[index] <= aMax[index]);
    }
#endif    // _DEBUG

    Rect rect;
    for (int axis = 0; axis < Dims; ++axis) {
        rect.m_min[axis] = aMin[axis];
        rect.m_max[axis] = aMax[axis];
    }

    InsertRect(&rect, aDataId, &m_root, 0);
}

RT_TEMPLATE
bool RT_QUAL::remove(const ElemType aMin[Dims], const ElemType aMax[Dims], const DataType& aDataId)
{
#ifdef _DEBUG
    for (int index = 0; index<Dims; ++index) {
        ASSERT(aMin[index] <= aMax[index]);
    }

#endif    // _DEBUG
    Rect rect;
    for (int axis = 0; axis < Dims; ++axis) {
        rect.m_min[axis] = aMin[axis];
        rect.m_max[axis] = aMax[axis];
    }

    return RemoveRect(&rect, aDataId, &m_root);
}

RT_TEMPLATE
int RT_QUAL::search(const ElemType aMin[Dims], const ElemType aMax[Dims], std::function<bool(const DataType&)> aCallback) const
{
#ifdef _DEBUG
    for (int index = 0; index < Dims; ++index) {
        ASSERT(aMin[index] <= aMax[index]);
    }

#endif    // _DEBUG

    Rect rect;
    for (int axis = 0; axis < Dims; ++axis) {
        rect.m_min[axis] = aMin[axis];
        rect.m_max[axis] = aMax[axis];
    }

    // NOTE: May want to return search result another way, perhaps returning the number of found elements here.
    int foundCount = 0;
    search(m_root, &rect, foundCount, aCallback);
    return foundCount;
}

RT_TEMPLATE
int RT_QUAL::search(const ElemType aMin[Dims], const ElemType aMax[Dims],
                    std::function<bool(const DataType&)> aCallback, bool& aFinished) const
{
#ifdef _DEBUG
    for (int index = 0; index < Dims; ++index) {
        ASSERT(aMin[index] <= aMax[index]);
    }

#endif // _DEBUG

    Rect rect;
    for (int axis = 0; axis < Dims; ++axis) {
        rect.m_min[axis] = aMin[axis];
        rect.m_max[axis] = aMax[axis];
    }

    // NOTE: May want to return search result another way, perhaps returning the number of found elements here.

    int foundCount = 0;
    aFinished      = search(m_root, &rect, foundCount, aCallback);
    return foundCount;
}


RT_TEMPLATE
std::vector<std::pair<ElemType, DataType>> RT_QUAL::nearestNeighbors(
        const ElemType a_point[Dims],
        std::function<bool(const std::size_t aNumResults, const ElemType aMinDist)> aTerminate,
        std::function<bool(const DataType aElement)> aFilter,
        std::function<ElemType(const ElemType a_point[Dims], const DataType a_data)> aSquaredDist) const
{
    std::vector<std::pair<ElemType, DataType>> result;
    std::priority_queue<NNNode> search_q;

    for (int i = 0; i < m_root->m_count; ++i) {
        if (m_root->IsLeaf()) {
            search_q.push(NNNode{m_root->m_branch[i], aSquaredDist(a_point, m_root->m_branch[i].m_data), m_root->IsLeaf()});
        } else {
            search_q.push(NNNode{m_root->m_branch[i], MinDist(a_point, m_root->m_branch[i].m_rect), m_root->IsLeaf()});
        }
    }

    while (!search_q.empty()) {
        const NNNode curNode = search_q.top();
        if (aTerminate(result.size(), curNode.minDist)) {
            break;
        }

        search_q.pop();

        if (curNode.isLeaf) {
            if (aFilter(curNode.m_branch.m_data)) {
                result.emplace_back(curNode.minDist, curNode.m_branch.m_data);
            }
        } else {
            Node* node = curNode.m_branch.m_child;

            for (int i = 0; i < node->m_count; ++i) {
                NNNode newNode;
                newNode.isLeaf = node->IsLeaf();
                newNode.m_branch = node->m_branch[i];
                if (newNode.isLeaf) {
                    newNode.minDist = aSquaredDist(a_point, newNode.m_branch.m_data);
                } else {
                    newNode.minDist = this->MinDist(a_point, node->m_branch[i].m_rect);
                }
                search_q.push(newNode);
            }
        }
    }

    return result;
}

RT_TEMPLATE
int RT_QUAL::count() const
{
    int count = 0;
    CountRec(m_root, count);
    return count;
}

RT_TEMPLATE
void RT_QUAL::CountRec(const Node* aNode, int& a_count) const
{
    if (aNode->IsInternalNode()) { // not a leaf node
        for (int index = 0; index < aNode->m_count; ++index) {
            CountRec(aNode->m_branch[index].m_child, a_count);
        }
    } else { // A leaf node
        a_count += aNode->m_count;
    }
}

RT_TEMPLATE
bool RT_QUAL::load(const char* aFileName)
{
    removeAll(); // Clear existing tree

    RTFileStream stream;
    if (!stream.OpenRead(aFileName)) {
        return false;
    }

    bool result = load(stream);
    stream.Close();

    return result;
}

RT_TEMPLATE
bool RT_QUAL::load(RTFileStream& a_stream) const
{
    // Write some kind of header
    int _dataFileId         = ('R' << 0) | ('T' << 8) | ('R' << 16) | ('E' << 24);
    int _dataSize           = sizeof(DataType);
    int _dataNumDims        = Dims;
    int _dataElemSize       = sizeof(ElemType);
    int _dataElemRealSize   = sizeof(ElemTypeReal);
    int _dataMaxNodes       = TMaxNodes;
    int _dataMinNodes       = TMinNodes;

    int dataFileId          = 0;
    int dataSize            = 0;
    int dataNumDims         = 0;
    int dataElemSize        = 0;
    int dataElemRealSize    = 0;
    int dataMaxNodes        = 0;
    int dataMinNodes        = 0;

    a_stream.Read(dataFileId);
    a_stream.Read(dataSize);
    a_stream.Read(dataNumDims);
    a_stream.Read(dataElemSize);
    a_stream.Read(dataElemRealSize);
    a_stream.Read(dataMaxNodes);
    a_stream.Read(dataMinNodes);

    bool result = false;

    // Test if header was valid and compatible
    if ((dataFileId == _dataFileId) && 
        (dataSize == _dataSize) &&
        (dataNumDims == _dataNumDims) &&
        (dataElemSize == _dataElemSize) &&
        (dataElemRealSize == _dataElemRealSize) &&
        (dataMaxNodes == _dataMaxNodes) &&
        (dataMinNodes == _dataMinNodes)) {
        // Recursively load tree
        result = LoadRec(m_root, a_stream);
    }

    return result;
}

RT_TEMPLATE
bool RT_QUAL::LoadRec(const Node* aNode, RTFileStream& a_stream) const
{
    a_stream.Read(aNode->m_level);
    a_stream.Read(aNode->m_count);

    if (aNode->IsInternalNode()) { // not a leaf node
        for (int index = 0; index < aNode->m_count; ++index) {
            const Branch* curBranch = &aNode->m_branch[index];

            a_stream.ReadArray(curBranch->m_rect.m_min, Dims);
            a_stream.ReadArray(curBranch->m_rect.m_max, Dims);

            curBranch->m_child = AllocNode();
            LoadRec(curBranch->m_child, a_stream);
        }
    } else { // A leaf node
        for (int index = 0; index < aNode->m_count; ++index) {
            const Branch* curBranch = &aNode->m_branch[index];

            a_stream.ReadArray(curBranch->m_rect.m_min, Dims);
            a_stream.ReadArray(curBranch->m_rect.m_max, Dims);

            a_stream.Read(curBranch->m_data);
        }
    }

    return true; // Should do more error checking on I/O operations
}

RT_TEMPLATE
bool RT_QUAL::save(const char* aFileName)
{
    RTFileStream stream;
    if (!stream.OpenWrite(aFileName)) {
        return false;
    }
    bool result = save(stream);
    stream.Close();
    return result;
}

RT_TEMPLATE
bool RT_QUAL::save(RTFileStream& a_stream) const
{
    // Write some kind of header
    int dataFileId          = ('R' << 0) | ('T' << 8) | ('R' << 16) | ('E' << 24);
    int dataSize            = sizeof(DataType);
    int dataNumDims         = Dims;
    int dataElemSize        = sizeof(ElemType);
    int dataElemRealSize    = sizeof(ElemTypeReal);
    int dataMaxNodes        = TMaxNodes;
    int dataMinNodes        = TMinNodes;

    a_stream.Write(dataFileId);
    a_stream.Write(dataSize);
    a_stream.Write(dataNumDims);
    a_stream.Write(dataElemSize);
    a_stream.Write(dataElemRealSize);
    a_stream.Write(dataMaxNodes);
    a_stream.Write(dataMinNodes);

    // Recursively save tree
    bool result = SaveRec(m_root, a_stream);

    return result;
}

RT_TEMPLATE
bool RT_QUAL::SaveRec(const Node* aNode, RTFileStream& a_stream) const
{
    a_stream.Write(aNode->m_level);
    a_stream.Write(aNode->m_count);

    if (aNode->IsInternalNode()) { // not a leaf node
        for (int index = 0; index < aNode->m_count; ++index) {
            const Branch* curBranch = &aNode->m_branch[index];

            a_stream.WriteArray(curBranch->m_rect.m_min, Dims);
            a_stream.WriteArray(curBranch->m_rect.m_max, Dims);

            SaveRec(curBranch->m_child, a_stream);
        }
    } else { // A leaf node
        for (int index = 0; index < aNode->m_count; ++index) {
            const Branch* curBranch = &aNode->m_branch[index];

            a_stream.WriteArray(curBranch->m_rect.m_min, Dims);
            a_stream.WriteArray(curBranch->m_rect.m_max, Dims);

            a_stream.Write(curBranch->m_data);
        }
    }

    return true; // Should do more error checking on I/O operations
}

RT_TEMPLATE
void RT_QUAL::removeAll()
{
    // Delete all existing nodes
    Reset();

    m_root = AllocNode();
    m_root->m_level = 0;
}

RT_TEMPLATE
void RT_QUAL::Reset() const
{
#ifdef RT_DONT_USE_MEMPOOLS
    // Delete all existing nodes
    RemoveAllRec(m_root);
#else    // RT_DONT_USE_MEMPOOLS
    // Just reset memory pools.  We are not using complex types
    // EXAMPLE
#endif    // RT_DONT_USE_MEMPOOLS
}

RT_TEMPLATE
void RT_QUAL::RemoveAllRec(Node* aNode) const
{
    ASSERT(aNode);
    ASSERT(aNode->m_level >= 0);

    if (aNode->IsInternalNode()) { // This is an internal node in the tree
        for (int index = 0; index < aNode->m_count; ++index) {
            RemoveAllRec(aNode->m_branch[index].m_child);
        }
    }

    FreeNode(aNode);
}

RT_TEMPLATE
typename RT_QUAL::Node* RT_QUAL::AllocNode() const
{
    Node* newNode;

#ifdef RT_DONT_USE_MEMPOOLS
    newNode = new Node;
#else       // RT_DONT_USE_MEMPOOLS
    // EXAMPLE
#endif      // RT_DONT_USE_MEMPOOLS
    InitNode(newNode);
    return newNode;
}

RT_TEMPLATE
void RT_QUAL::FreeNode(Node* aNode) const
{
    ASSERT(aNode);

#ifdef RT_DONT_USE_MEMPOOLS
    delete aNode;
#else       // RT_DONT_USE_MEMPOOLS
    // EXAMPLE
#endif      // RT_DONT_USE_MEMPOOLS
}

// Allocate space for a node in the list used in DeletRect to
// store Nodes that are too empty.
RT_TEMPLATE
typename RT_QUAL::ListNode* RT_QUAL::AllocListNode() const
{
#ifdef RT_DONT_USE_MEMPOOLS
    return new ListNode;
#else       // RT_DONT_USE_MEMPOOLS
    // EXAMPLE
#endif      // RT_DONT_USE_MEMPOOLS
}

RT_TEMPLATE
void RT_QUAL::FreeListNode(ListNode* aListNode) const
{
#ifdef RT_DONT_USE_MEMPOOLS
    delete aListNode;
#else       // RT_DONT_USE_MEMPOOLS
    // EXAMPLE
#endif      // RT_DONT_USE_MEMPOOLS
}

RT_TEMPLATE
void RT_QUAL::InitNode(Node* aNode) const
{
    aNode->m_count = 0;
    aNode->m_level = -1;
}

RT_TEMPLATE
void RT_QUAL::InitRect(Rect* aRect) const
{
    for (int index = 0; index < Dims; ++index) {
        aRect->m_min[index] = (ElemType) 0;
        aRect->m_max[index] = (ElemType) 0;
    }
}

// Inserts a new data rectangle into the index structure.
// Recursively descends tree, propagates splits back up.
// Returns 0 if node was not split.  Old node updated.
// If node was split, returns 1 and sets the pointer pointed to by
// new_node to point to the new node.  Old node updated to become one of two.
// The level argument specifies the number of steps up from the leaf
// level to insert; e.g. a data rectangle goes in at level = 0.
RT_TEMPLATE
bool RT_QUAL::InsertRectRec(const Rect* aRect, const DataType& aId, Node* aNode, Node** aNewNode, int aLevel) const
{
    ASSERT(aRect && aNode && aNewNode);
    ASSERT(aLevel >= 0 && aLevel <= aNode->m_level);

    int     index;
    Branch  branch;
    Node*   otherNode;

    // Still above level for insertion, go down tree recursively
    if (aNode->m_level > aLevel) {
        index = PickBranch(aRect, aNode);

        if (!InsertRectRec(aRect, aId, aNode->m_branch[index].m_child, &otherNode, aLevel)) {
            // Child was not split
            aNode->m_branch[index].m_rect =
                    CombineRect(aRect, &(aNode->m_branch[index].m_rect));
            return false;
        } else { // Child was split
            aNode->m_branch[index].m_rect = NodeCover(aNode->m_branch[index].m_child);
            branch.m_child  = otherNode;
            branch.m_rect   = NodeCover(otherNode);
            return AddBranch(&branch, aNode, aNewNode);
        }
    } else if (aNode->m_level == aLevel) {// Have reached level for insertion. Add rect, split if necessary
        branch.m_rect   = *aRect;
        branch.m_child  = (Node*) aId;
        // Child field of leaves contains id of data record
        return AddBranch(&branch, aNode, aNewNode);
    } else {
        // Should never occur
        ASSERT(0);
        return false;
    }
}

// Insert a data rectangle into an index structure.
// InsertRect provides for splitting the root;
// returns 1 if root was split, 0 if it was not.
// The level argument specifies the number of steps up from the leaf
// level to insert; e.g. a data rectangle goes in at level = 0.
// InsertRect2 does the recursion.
//
RT_TEMPLATE
bool RT_QUAL::InsertRect(const Rect* aRect, const DataType& aId, Node** aRoot, int aLevel) const
{
    ASSERT(aRect && aRoot);
    ASSERT(aLevel >= 0 && aLevel <= (*aRoot)->m_level);
#ifdef _DEBUG
    for (int index = 0; index < Dims; ++index) {
        ASSERT(aRect->m_min[index] <= aRect->m_max[index]);
    }
#endif    // _DEBUG

    Node*   newRoot;
    Node*   newNode;
    Branch  branch;

    if (InsertRectRec(aRect, aId, *aRoot, &newNode, aLevel)) { // Root split
        newRoot = AllocNode();                                      // Grow tree taller and new root
        newRoot->m_level    = (*aRoot)->m_level + 1;
        branch.m_rect       = NodeCover(*aRoot);
        branch.m_child      = *aRoot;
        AddBranch(&branch, newRoot, nullptr);
        branch.m_rect   = NodeCover(newNode);
        branch.m_child  = newNode;
        AddBranch(&branch, newRoot, nullptr);
        *aRoot = newRoot;
        return true;
    }

    return false;
}

// Find the smallest rectangle that includes all rectangles in branches of a node.
RT_TEMPLATE
typename RT_QUAL::Rect RT_QUAL::NodeCover(Node* aNode) const
{
    ASSERT(aNode);

    bool firstTime = true;
    Rect rect;
    InitRect(&rect);

    for (int index = 0; index < aNode->m_count; ++index) {
        if (firstTime) {
            rect = aNode->m_branch[index].m_rect;
            firstTime = false;
        } else {
            rect = CombineRect(&rect, &(aNode->m_branch[index].m_rect));
        }
    }

    return rect;
}

// Add a branch to a node.  Split the node if necessary.
// Returns 0 if node not split.  Old node updated.
// Returns 1 if node split, sets *new_node to address of new node.
// Old node updated, becomes one of two.
RT_TEMPLATE
bool RT_QUAL::AddBranch(const Branch* aBranch, Node* aNode, Node** aNewNode) const
{
    ASSERT(aBranch);
    ASSERT(aNode);

    if (aNode->m_count < MaxNodes) {// Split won't be necessary
        aNode->m_branch[aNode->m_count] = *aBranch;
        ++aNode->m_count;

        return false;
    } else {
        ASSERT(aNewNode);

        SplitNode(aNode, aBranch, aNewNode);
        return true;
    }
}

// Disconnect a dependent node.
// Caller must return (or stop using iteration index) after this as count has changed
RT_TEMPLATE
void RT_QUAL::DisconnectBranch(Node* aNode, int aIndex) const
{
    ASSERT(aNode && (aIndex >= 0) && (aIndex < MaxNodes));
    ASSERT(aNode->m_count > 0);

    // Remove element by swapping with the last element to prevent gaps in array
    aNode->m_branch[aIndex] = aNode->m_branch[aNode->m_count - 1];

    --aNode->m_count;
}

// Pick a branch.  Pick the one that will need the smallest increase
// in area to accomodate the new rectangle.  This will result in the
// least total area for the covering rectangles in the current node.
// In case of a tie, pick the one which was smaller before, to get
// the best resolution when searching.
RT_TEMPLATE
int RT_QUAL::PickBranch(const Rect* aRect, Node* aNode) const
{
    ASSERT(aRect && aNode);

    bool            firstTime = true;
    ElemTypeReal    increase;
    ElemTypeReal    bestIncr = (ElemTypeReal) -1;
    ElemTypeReal    area;
    ElemTypeReal    bestArea = 0;
    int             best = 0;
    Rect            tempRect;

    for (int index = 0; index < aNode->m_count; ++index) {
        Rect *curRect = &aNode->m_branch[index].m_rect;
        area = CalcRectVolume(curRect);
        tempRect = CombineRect(aRect, curRect);
        increase = CalcRectVolume(&tempRect) - area;

        if ((increase < bestIncr) || firstTime) {
            best = index;
            bestArea = area;
            bestIncr = increase;
            firstTime = false;
        } else if ((increase == bestIncr) && (area < bestArea)) {
            best = index;
            bestArea = area;
            bestIncr = increase;
        }
    }

    return best;
}

// Combine two rectangles into larger one containing both
RT_TEMPLATE
typename RT_QUAL::Rect RT_QUAL::CombineRect(const Rect* aRectA, const Rect* aRectB) const
{
    ASSERT(aRectA && aRectB);

    Rect newRect;
    for (int index = 0; index < Dims; ++index) {
        newRect.m_min[index] = std::min(aRectA->m_min[index], aRectB->m_min[index]);
        newRect.m_max[index] = std::max(aRectA->m_max[index], aRectB->m_max[index]);
    }
    return newRect;
}

// Split a node.
// Divides the nodes branches and the extra one between two nodes.
// Old node is one of the new ones, and one really new one is created.
// Tries more than one method for choosing a partition, uses best result.
RT_TEMPLATE
void RT_QUAL::SplitNode(Node* aNode, const Branch* aBranch, Node** aNewNode) const
{
    ASSERT(aNode);
    ASSERT(aBranch);

    // Could just use local here, but member or external is faster since it is reused
    PartitionVars   localVars;
    PartitionVars*  parVars = &localVars;
    int             level;

    // Load all the branches into a buffer, initialize old node
    level = aNode->m_level;
    GetBranches(aNode, aBranch, parVars);

    // Find partition
    ChoosePartition(parVars, MinNodes);

    // Put branches from buffer into 2 nodes according to chosen partition
    *aNewNode = AllocNode();
    (*aNewNode)->m_level = aNode->m_level = level;
    LoadNodes(aNode, *aNewNode, parVars);

    ASSERT((aNode->m_count + (*aNewNode)->m_count) == parVars->m_total);
}

// Calculate the n-dimensional volume of a rectangle
RT_TEMPLATE
ElemTypeReal RT_QUAL::RectVolume(const Rect* aRect) const
{
    ASSERT(aRect);

    ElemTypeReal volume = (ElemTypeReal) 1;
    for (int index = 0; index<Dims; ++index) {
        volume *= aRect->m_max[index] - aRect->m_min[index];
    }
    ASSERT(volume >= (ElemTypeReal) 0);

    return volume;
}

// The exact volume of the bounding sphere for the given Rect
RT_TEMPLATE
ElemTypeReal RT_QUAL::RectSphericalVolume(const Rect* aRect) const
{
    ASSERT(aRect);

    ElemTypeReal sumOfSquares = (ElemTypeReal) 0;

    for (int index = 0; index < Dims; ++index) {
        ElemTypeReal halfExtent = ((ElemTypeReal) aRect->m_max[index] - (ElemTypeReal) aRect->m_min[index]) * 0.5f;
        sumOfSquares += halfExtent * halfExtent;
    }

    // Pow maybe slow, so test for common dims like 2,3 and just use x*x, x*x*x.
    if (Dims == 2) {
        return sumOfSquares * m_unitSphereVolume;
    } else if (Dims == 3) {
        ElemTypeReal radius = (ElemTypeReal) std::sqrt(sumOfSquares);

        return radius * radius * radius * m_unitSphereVolume;
    } else {
        ElemTypeReal radius = (ElemTypeReal) std::sqrt(sumOfSquares);

        return (ElemTypeReal) (std::pow(radius, Dims) * m_unitSphereVolume);
    }
}

// Use one of the methods to calculate retangle volume
RT_TEMPLATE
ElemTypeReal RT_QUAL::CalcRectVolume(const Rect* aRect) const
{
#ifdef RT_USE_SPHERICAL_VOLUME
    return RectSphericalVolume(aRect);   // Slower but helps certain merge cases
#else                                       // RT_USE_SPHERICAL_VOLUME
    return RectVolume(aRect);            // Faster but can cause poor merges
#endif                                      // RT_USE_SPHERICAL_VOLUME
}

// Load branch buffer with branches from full node plus the extra branch.
RT_TEMPLATE
void RT_QUAL::GetBranches(Node* aNode, const Branch* aBranch, PartitionVars* aParVars) const
{
    ASSERT(aNode);
    ASSERT(aBranch);

    ASSERT(aNode->m_count == MaxNodes);

    // Load the branch buffer
    for (int index = 0; index < MaxNodes; ++index) {
        aParVars->m_branchBuf[index] = aNode->m_branch[index];
    }

    aParVars->m_branchBuf[MaxNodes] = *aBranch;
    aParVars->m_branchCount = MaxNodes + 1;

    // Calculate rect containing all in the set
    aParVars->m_coverSplit = aParVars->m_branchBuf[0].m_rect;

    for (int index = 1; index < MaxNodes + 1; ++index) {
        aParVars->m_coverSplit = CombineRect(&aParVars->m_coverSplit, &aParVars->m_branchBuf[index].m_rect);
    }

    aParVars->m_coverSplitArea = CalcRectVolume(&aParVars->m_coverSplit);

    InitNode(aNode);
}

// Method #0 for choosing a partition:
// As the seeds for the two groups, pick the two rects that would waste the
// most area if covered by a single rectangle, i.e. evidently the worst pair
// to have in the same group.
// Of the remaining, one at a time is chosen to be put in one of the two groups.
// The one chosen is the one with the greatest difference in area expansion
// depending on which group - the rect most strongly attracted to one group
// and repelled from the other.
// If one group gets too full (more would force other group to violate min
// fill requirement) then other group gets the rest.
// These last are the ones that can go in either group most easily.
RT_TEMPLATE
void RT_QUAL::ChoosePartition(PartitionVars* aParVars, int aMinFill) const
{
    ASSERT(aParVars);

    ElemTypeReal biggestDiff;
    int group, chosen = 0, betterGroup = 0;

    InitParVars(aParVars, aParVars->m_branchCount, aMinFill);
    PickSeeds(aParVars);

    while (((aParVars->m_count[0] + aParVars->m_count[1]) < aParVars->m_total) &&
           (aParVars->m_count[0] < (aParVars->m_total - aParVars->m_minFill)) &&
           (aParVars->m_count[1] < (aParVars->m_total - aParVars->m_minFill))) {
        biggestDiff = (ElemTypeReal) -1;

        for (int index = 0; index < aParVars->m_total; ++index) {
            if (!aParVars->m_taken[index]) {
                const Rect *curRect = &aParVars->m_branchBuf[index].m_rect;
                const Rect rect0 = CombineRect(curRect, &aParVars->m_cover[0]);
                const Rect rect1 = CombineRect(curRect, &aParVars->m_cover[1]);
                ElemTypeReal growth0 = CalcRectVolume(&rect0) - aParVars->m_area[0];
                ElemTypeReal growth1 = CalcRectVolume(&rect1) - aParVars->m_area[1];
                ElemTypeReal diff = growth1 - growth0;

                if (diff >= 0) {
                    group = 0;
                } else {
                    group = 1;
                    diff = -diff;
                }

                if (diff > biggestDiff) {
                    biggestDiff = diff;
                    chosen = index;
                    betterGroup = group;
                } else if ((diff == biggestDiff) && (aParVars->m_count[group] < aParVars->m_count[betterGroup])) {
                    chosen = index;
                    betterGroup = group;
                }
            }
        }
        Classify(chosen, betterGroup, aParVars);
    }

    // If one group too full, put remaining rects in the other
    if ((aParVars->m_count[0] + aParVars->m_count[1]) < aParVars->m_total) {
        if (aParVars->m_count[0] >= aParVars->m_total - aParVars->m_minFill) {
            group = 1;
        } else {
            group = 0;
        }

        for (int index = 0; index < aParVars->m_total; ++index) {
            if (!aParVars->m_taken[index]) {
                Classify(index, group, aParVars);
            }
        }
    }

    ASSERT((aParVars->m_count[0] + aParVars->m_count[1]) == aParVars->m_total);
    ASSERT((aParVars->m_count[0] >= aParVars->m_minFill) && (aParVars->m_count[1] >= aParVars->m_minFill));
}

// Copy branches from the buffer into two nodes according to the partition.
RT_TEMPLATE
void RT_QUAL::LoadNodes(Node* a_nodeA, Node* aNodeB, PartitionVars* aParVars) const
{
    ASSERT(a_nodeA);
    ASSERT(aNodeB);
    ASSERT(aParVars);

    for (int index = 0; index < aParVars->m_total; ++index) {
        ASSERT(aParVars->m_partition[index] == 0 || aParVars->m_partition[index] == 1);

        if (aParVars->m_partition[index] == 0) {
            AddBranch(&aParVars->m_branchBuf[index], a_nodeA, nullptr);
        } else if (aParVars->m_partition[index] == 1) {
            AddBranch(&aParVars->m_branchBuf[index], aNodeB, nullptr);
        }
    }
}

// Initialize a PartitionVars structure.
RT_TEMPLATE
void RT_QUAL::InitParVars(PartitionVars* aParVars, int aMaxRects, int aMinFill) const
{
    ASSERT(aParVars);

    aParVars->m_count[0] = aParVars->m_count[1] = 0;
    aParVars->m_area[0]  = aParVars->m_area[1] = (ElemTypeReal) 0;
    aParVars->m_total    = aMaxRects;
    aParVars->m_minFill  = aMinFill;

    for (int index = 0; index < aMaxRects; ++index) {
        aParVars->m_taken[index] = false;
        aParVars->m_partition[index] = -1;
    }
}

RT_TEMPLATE
void RT_QUAL::PickSeeds(PartitionVars* aParVars) const
{
    int             seed0 = 0, seed1 = 0;
    ElemTypeReal    worst, waste;
    ElemTypeReal    area[MaxNodes + 1];

    for (int index = 0; index<aParVars->m_total; ++index)
    {
        area[index] = CalcRectVolume(&aParVars->m_branchBuf[index].m_rect);
    }

    worst = -aParVars->m_coverSplitArea - 1;

    for (int indexA = 0; indexA < aParVars->m_total - 1; ++indexA)
    {
        for (int indexB = indexA + 1; indexB < aParVars->m_total; ++indexB)
        {
            Rect oneRect = CombineRect(&aParVars->m_branchBuf[indexA].m_rect,
                                        &aParVars->m_branchBuf[indexB].m_rect);
            waste = CalcRectVolume(&oneRect) - area[indexA] - area[indexB];

            if (waste >= worst)
            {
                worst   = waste;
                seed0   = indexA;
                seed1   = indexB;
            }
        }
    }

    Classify(seed0, 0, aParVars);
    Classify(seed1, 1, aParVars);
}


// Put a branch in one of the groups.
RT_TEMPLATE
void RT_QUAL::Classify(int aIndex, int aGroup, PartitionVars* aParVars) const
{
    ASSERT(aParVars);
    ASSERT(!aParVars->m_taken[aIndex]);

    aParVars->m_partition[aIndex] = aGroup;
    aParVars->m_taken[aIndex]     = true;

    if (aParVars->m_count[aGroup] == 0)
    {
        aParVars->m_cover[aGroup] = aParVars->m_branchBuf[aIndex].m_rect;
    }
    else
    {
        aParVars->m_cover[aGroup] = CombineRect(&aParVars->m_branchBuf[aIndex].m_rect,
                                                   &aParVars->m_cover[aGroup]);
    }

    aParVars->m_area[aGroup] = CalcRectVolume(&aParVars->m_cover[aGroup]);
    ++aParVars->m_count[aGroup];
}


// Delete a data rectangle from an index structure.
// Pass in a pointer to a Rect, the tid of the record, ptr to ptr to root node.
// Returns 1 if record not found, 0 if success.
// RemoveRect provides for eliminating the root.
RT_TEMPLATE
bool RT_QUAL::RemoveRect(const Rect* aRect, const DataType& aId, Node** aRoot) const
{
    ASSERT(aRect && aRoot);
    ASSERT(*aRoot);

    Node*       tempNode;
    ListNode*   reInsertList = nullptr;

    if (!RemoveRectRec(aRect, aId, *aRoot, &reInsertList))
    {
        // Found and deleted a data item
        // Reinsert any branches from eliminated nodes
        while (reInsertList)
        {
            tempNode = reInsertList->m_node;

            for (int index = 0; index < tempNode->m_count; ++index)
            {
                InsertRect(&(tempNode->m_branch[index].m_rect),
                            tempNode->m_branch[index].m_data,
                            aRoot,
                            tempNode->m_level);
            }

            ListNode* remLNode = reInsertList;
            reInsertList = reInsertList->m_next;

            FreeNode(remLNode->m_node);
            FreeListNode(remLNode);
        }

        // Check for redundant root (not leaf, 1 child) and eliminate
        if((*aRoot)->m_count == 1 && (*aRoot)->IsInternalNode())
        {
            tempNode = (*aRoot)->m_branch[0].m_child;

            ASSERT(tempNode);
            FreeNode(*aRoot);
            *aRoot = tempNode;
        }

        return false;
    }
    else
    {
        return true;
    }
}


// Delete a rectangle from non-root part of an index structure.
// Called by RemoveRect.  Descends tree recursively,
// merges branches on the way back up.
// Returns 1 if record not found, 0 if success.
RT_TEMPLATE
bool RT_QUAL::RemoveRectRec(const Rect*     aRect,
                                const DataType& aId,
                                Node*           aNode,
                                ListNode**      aListNode) const
{
    ASSERT(aRect && aNode && aListNode);
    ASSERT(aNode->m_level >= 0);

    if (aNode->IsInternalNode()) // not a leaf node
    {
        for (int index = 0; index < aNode->m_count; ++index)
        {
            if (Overlap(aRect, &(aNode->m_branch[index].m_rect)))
            {
                if (!RemoveRectRec(aRect, aId, aNode->m_branch[index].m_child, aListNode))
                {
                    if (aNode->m_branch[index].m_child->m_count >= MinNodes)
                    {
                        // child removed, just resize parent rect
                        aNode->m_branch[index].m_rect =
                                NodeCover(aNode->m_branch[index].m_child);
                    }
                    else
                    {
                        // child removed, not enough entries in node, eliminate node
                        ReInsert(aNode->m_branch[index].m_child, aListNode);
                        DisconnectBranch(aNode, index); // Must return after this call as count has changed
                    }

                    return false;
                }
            }
        }

        return true;
    }
    else // A leaf node
    {
        for (int index = 0; index < aNode->m_count; ++index)
        {
            if (aNode->m_branch[index].m_child == (Node*) aId)
            {
                DisconnectBranch(aNode, index); // Must return after this call as count has changed
                return false;
            }
        }

        return true;
    }
}


// Decide whether two rectangles overlap.
RT_TEMPLATE
bool RT_QUAL::Overlap(const Rect* aRectA, const Rect* aRectB)
{
    ASSERT(aRectA && aRectB);

    for (int index = 0; index < Dims; ++index)
    {
        if (aRectA->m_min[index] > aRectB->m_max[index]
            || aRectB->m_min[index] > aRectA->m_max[index])
        {
            return false;
        }
    }

    return true;
}


// Add a node to the reinsertion list.  All its branches will later
// be reinserted into the index structure.
RT_TEMPLATE
void RT_QUAL::ReInsert(Node* aNode, ListNode** aListNode) const
{
    ListNode* newListNode;

    newListNode = AllocListNode();
    newListNode->m_node = aNode;
    newListNode->m_next = *aListNode;
    *aListNode = newListNode;
}


// Search in an index tree or subtree for all data rectangles that overlap the argument rectangle.
RT_TEMPLATE
bool RT_QUAL::Search(const Node* aNode, const Rect* aRect, int& a_foundCount,
                         std::function<bool(const DataType&)> aCallback) const
{
    ASSERT(aNode);
    ASSERT(aNode->m_level >= 0);
    ASSERT(aRect);

    if (aNode->IsInternalNode()) // This is an internal node in the tree
    {
        for (int index = 0; index < aNode->m_count; ++index)
        {
            if (Overlap(aRect, &aNode->m_branch[index].m_rect))
            {
                if (!search(aNode->m_branch[index].m_child, aRect, a_foundCount, aCallback))
                {
                    return false; // Don't continue searching
                }
            }
        }
    }
    else // This is a leaf node
    {
        for (int index = 0; index < aNode->m_count; ++index)
        {
            if (Overlap(aRect, &aNode->m_branch[index].m_rect))
            {
                DataType& id = aNode->m_branch[index].m_data;
                ++a_foundCount;

                if (aCallback && !aCallback(id))
                {
                    return false; // Don't continue searching
                }
            }
        }
    }

    return true; // Continue searching
}


//calculate the minimum distance between a point and a rectangle as defined by Manolopoulos et al.
// returns Euclidean norm to ensure value fits in ElemType
RT_TEMPLATE
ElemType RT_QUAL::MinDist(const ElemType a_point[Dims], const Rect& aRect) const
{
    const ElemType *q, *s, *t;
    q = a_point;
    s = aRect.m_min;
    t = aRect.m_max;
    double minDist = 0.0;

    for (int index = 0; index < Dims; index++)
    {
        int r = q[index];

        if (q[index] < s[index])
        {
            r = s[index];
        }
        else if (q[index] > t[index])
        {
            r = t[index];
        }

        double addend = q[index] - r;
        minDist += addend * addend;
    }

    return std::lround(std::sqrt(minDist));
}

#undef RT_TEMPLATE
#undef RT_QUAL