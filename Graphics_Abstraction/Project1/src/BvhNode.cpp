#include "BvhNode.h"


BvhNode::BvhNode( const cAABB& aabb) : leftChild(nullptr), rightChild(nullptr)
{
  
}

BvhNode::BvhNode(const cAABB& aabb, const std::vector<Triangle>& triangles, std::vector<int> triangleIndices, int nodeIndex, BvhNode* parentNode, Model* model) 
	: aabb(aabb), leftChild(nullptr), rightChild(nullptr)
{
	this->aabb = aabb;
	this->nodeIndex = nodeIndex;
	this->rootNode = parentNode;

	if (triangleIndices.size() == 0)
	{
		for (int i = 0; i < (int)triangles.size(); i++)
		{
			this->trianglesIndex.push_back(i);
		}
		RecursiveSplit(triangles);
		this->trianglesIndex.clear();
		return;
	}

	for (size_t i = 0; i < triangleIndices.size(); i++)
	{
		int triangleIndex = triangleIndices[i];
		glm::vec3 collisionPoint;

		if (CollisionAABBVsTriangle(aabb, triangles[triangleIndex], collisionPoint))
		{
			this->trianglesIndex.push_back(triangleIndex);
		}
	}


	if (nodeIndex < AABBDepth)
	{
		if ((int)this->trianglesIndex.size() > maxtriCount)
		{
			RecursiveSplit(triangles);
			this->trianglesIndex.clear();
		}
	}

}

BvhNode::~BvhNode()
{
	delete leftChild;
	delete rightChild;
}

cAABB BvhNode::GetModelAABB()
{
	return aabb;
}

void BvhNode::RecursiveSplit(const std::vector<Triangle>& triangleList)
{
	int MaxextendAxis = FindMaxExtentAxis(aabb);

	float spitPos = 0.5f * (aabb.minV[MaxextendAxis] + aabb.maxV[MaxextendAxis]);

	cAABB leftAABB = aabb;
	leftAABB.maxV[MaxextendAxis] = spitPos;

	cAABB rightAABB = aabb;
	rightAABB.minV[MaxextendAxis] = spitPos;


	std::vector<int> leftTriangleIndices;
	std::vector<int> rightTriangleIndices;

	for (int i : trianglesIndex)
	{
		leftTriangleIndices.push_back(i);
		rightTriangleIndices.push_back(i);
	}

	leftChild = new BvhNode(leftAABB, triangleList, leftTriangleIndices, (nodeIndex + 1), this, model);
	rightChild = new BvhNode(rightAABB, triangleList, rightTriangleIndices, (nodeIndex + 1), this, model);


}
