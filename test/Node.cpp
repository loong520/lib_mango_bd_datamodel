//
// Created by 18224 on 2025/5/19.
//

#include "doctest.h"
#include "Node.h"

using namespace mango::blockdiagram::datamodel;

TEST_CASE("Node::createNode")
{
    auto n1 = Node::New(nullptr);
    REQUIRE(n1 != nullptr);
    // 类型检查
    REQUIRE(n1->isTypeOf(ObjectType::kNode));
    REQUIRE(n1->isTypeOf(ObjectType::kGraphElement));
    REQUIRE(n1->isTypeOf(ObjectType::kGObject));
    REQUIRE(n1->isTypeOf(ObjectType::kObject));
    // 父节点检查
    REQUIRE(n1->getParent() == nullptr);
    // 根节点检查
    REQUIRE(n1->isRootNode());
    // 层次结构检查
    REQUIRE_FALSE(n1->isHierarchical());
    // 大小初始化检查
    REQUIRE(n1->getShape() != nullptr);
    REQUIRE_EQ(n1->getSize(), QSize(0, 0));     // 根节点的大小为0
    // 成员检查
    REQUIRE_EQ(n1->getGraphElements().size(), 0);
    REQUIRE_EQ(n1->getSubNodes().size(), 0);
    REQUIRE_EQ(n1->getIndependentPin().size(), 0);
    REQUIRE_EQ(n1->getNets().size(), 0);
}

TEST_CASE("Node::createSubNode")
{
    auto n1 = Node::New(nullptr);
    REQUIRE(n1!= nullptr);
    auto n2 = Node::New(n1);    // 创建子节点
    REQUIRE(n2!= nullptr);
    // 类型检查
    REQUIRE(n2->isTypeOf(ObjectType::kNode));
    REQUIRE(n2->isTypeOf(ObjectType::kGraphElement));
    REQUIRE(n2->isTypeOf(ObjectType::kGObject));
    REQUIRE(n2->isTypeOf(ObjectType::kObject));
    // 父节点检查
    REQUIRE_EQ(n2->getParent(), n1);
    // 根节点检查
    REQUIRE(n1->isRootNode());
    REQUIRE_FALSE(n2->isRootNode());
    // 层次结构检查
    REQUIRE(n1->isHierarchical());
    REQUIRE_FALSE(n2->isHierarchical());
    // 大小初始化检查
    REQUIRE_EQ(n1->getSize(), QSize(0, 0));     // 根节点的大小为0
    REQUIRE_EQ(n2->getSize(), QSize(120, 200));     // 子节点的大小为0

    auto rect2 = n2->getBoundingRect();
    REQUIRE_EQ(rect2.width(), 120);
    REQUIRE_EQ(rect2.height(), 200);
    REQUIRE_EQ(rect2.topLeft(), QPointF(0, 0));
    // 成员检查
    REQUIRE_EQ(n1->getGraphElements().size(), 0);
    REQUIRE_EQ(n1->getSubNodes().size(), 1);
    REQUIRE_EQ(n1->getIndependentPin().size(), 0);
    REQUIRE_EQ(n1->getNets().size(), 0);
}