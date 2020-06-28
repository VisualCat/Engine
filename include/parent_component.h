#pragma once

#include <platform_types.h>
#include <transform_component.h>

struct Parent {
	u32 parent_entity;
	Transform relative_transform;
};