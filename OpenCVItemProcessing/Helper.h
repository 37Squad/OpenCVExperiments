#pragma once

static bool IN_RANGE(int x, int y, int z)
{
	return (x >= y && x <= z) ? true : false;
}