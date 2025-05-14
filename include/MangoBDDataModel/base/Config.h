//
// Created by 18224 on 2025/5/7.
//

#pragma once

#if defined(MANGO_BD_DATAMODEL_EXPORTS)
#  define MANGO_BD_DATAMODEL_API __declspec(dllexport)
#else
#  define MANGO_BD_DATAMODEL_API __declspec(dllimport)
#endif
