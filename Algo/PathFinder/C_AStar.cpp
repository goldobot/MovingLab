#include "C_AStar.h"

SearchNode::SearchNode()
{
    type = WAYNODE;
    originX = 0;
    originY = 0;
    h = numeric_limits<double>::max();
    g = numeric_limits<UINT>::max();
    expandCost = 1;
    cost = numeric_limits<double>::max();
    pathCost = numeric_limits<double>::max();
}

SearchNode::~SearchNode()
{

}

PathNode::PathNode()
{
    x = 0;
    y = 0;
}

PathNode::~PathNode()
{

}

NodeState::NodeState()
{
    x = 0;
    y = 0;

    state = NONE;
}

NodeState::NodeState(UINT x, UINT y, NodeType state)
{
    this->x = x;
    this->y = y;
    this->state = state;
    this->ancestor = SELF;
}

NodeState::~NodeState()
{

}

C_AStar::C_AStar()
{
    m_nodesMatrix = NULL;
    m_mapWidth = 0;
    m_mapHeight = 0;
    heuristic = AStarHeuristics::euclidean;

    m_startNode.first = 0;
    m_startNode.second = 0;
    m_endNode.first = 0;
    m_endNode.second = 0;
    m_rawPath.clear();
    m_marginPath.clear();
    m_directPath.clear();
    openedNodes.clear();
    matrixsChanges.clear();
    //ready = false;
}

C_AStar::C_AStar(UINT width, UINT height)
{
    m_nodesMatrix = new SearchNode [width * height];

    this->m_mapWidth = width;
    this->m_mapHeight = height;
    m_startNode.first = 0;
    m_startNode.second = 0;
    m_endNode.first = 0;
    m_endNode.second = 0;
    m_rawPath.clear();
    m_marginPath.clear();
    m_directPath.clear();
    openedNodes.clear();
    matrixsChanges.clear();
    //ready = true;
}

C_AStar::~C_AStar()
{
    DestroyMatrix();
}

void C_AStar::ComputeCost(pair<UINT, UINT> node)
{
    SearchNode * currentNode = m_nodesMatrix + node.second * m_mapWidth + node.first;
    SearchNode * origineNode = m_nodesMatrix + (currentNode->originY) * m_mapWidth + currentNode->originX;

    double x_minus_destX = (double)node.first - (double)m_endNode.first;
    double y_minus_destY = (double)node.second - (double)m_endNode.second;

    if (heuristic == euclidean)             currentNode->h = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
    else if (heuristic == manhattan)		currentNode->h = abs(x_minus_destX) + abs(y_minus_destY);
    else if (heuristic == diagonal)			currentNode->h = max(abs(x_minus_destX), abs(y_minus_destY));
    else if (heuristic == newH)
    {
        double euc = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
        currentNode->h = ceil(euc) - euc;
    }
    else                                    currentNode->h = 0.0;

    //currentNode->h = h;
    currentNode->g = origineNode->g + currentNode->expandCost;
    currentNode->cost = (currentNode->h) + (double)(currentNode->g);
    currentNode->pathCost = origineNode->pathCost + currentNode->cost;
}

void C_AStar::OpenNode(UINT x, UINT y, UINT originX, UINT originY)
{
    NodeState nodeState;
    double orignalPathCost, newPathCost;
    UINT predX, predY;

    if (x >= m_mapWidth       || y >= m_mapHeight)		return;
    if (originX >= m_mapWidth || originY >= m_mapHeight)	return;

    SearchNode * currentNode = m_nodesMatrix + y * m_mapWidth + x;


    if (currentNode->type == WALLNODE || currentNode->type == VISITEDNODE) return;
    else if (currentNode->type == WAYNODE)
    {
        currentNode->type = OPENEDNODE;
        openedNodes.push_back(pair<UINT, UINT>(x, y));
    }
    else if (currentNode->cost < EtimateCost(originX, originY, x, y))
    {
        return;
    }
    else if (currentNode->expandCost != 1)
    {
        orignalPathCost = PathCostToNode(currentNode->originX, currentNode->originY, x, y);
        newPathCost = PathCostToNode(originX, originY, x, y);

        predX = currentNode->originX;
        predY = currentNode->originY;

        if (orignalPathCost < newPathCost) return;
    }

    SetOriginNode(x, y, originX, originY);
    ComputeCost(pair<UINT, UINT>(x, y));
}

void C_AStar::FreeNodes()
{
    //if (ready)			return;
    //if (m_nodesMatrix == NULL)	return;

    UINT nbNodes = m_mapWidth * m_mapHeight;

    for (UINT i = 0; i < nbNodes;  i++)
        if (m_nodesMatrix[i].type != WALLNODE)
            m_nodesMatrix[i].type = WAYNODE;

    //ready = true;
}

void C_AStar::SetOriginNode(UINT x, UINT y, UINT originX, UINT originY)
{
    if (x >= m_mapWidth || y >= m_mapHeight)				return;
    if (originX >= m_mapWidth || originY >= m_mapHeight)	return;

    SearchNode * currentNode = m_nodesMatrix + y * m_mapWidth + x;

    currentNode->originX = originX;
    currentNode->originY = originY;
}

double C_AStar::PathCostToNode(UINT x, UINT y, UINT destX, UINT destY)
{
    double cost = 0.0;

    SearchNode * currentNode = m_nodesMatrix + y * m_mapWidth + x;

    UINT originX = currentNode->originX;
    UINT originY = currentNode->originY;

    while (!(originX == x && originY == y))
    {
        double x_minus_destX = (double)x - (double)destX;
        double y_minus_destY = (double)y - (double)destY;

        double h = 0.0;

        if (heuristic == euclidean)             h = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
        else if (heuristic == manhattan)		h = abs(x_minus_destX) + abs(y_minus_destY);
        else if (heuristic == diagonal)			h = max(abs(x_minus_destX), abs(y_minus_destY));
        else if (heuristic == newH)
        {
            double euc = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
            h = ceil(euc) - euc;
        }

        cost += h + currentNode->expandCost;

        x = originX;
        y = originY;
        currentNode = m_nodesMatrix + y * m_mapWidth + x;

        originX = currentNode->originX;
        originY = currentNode->originY;
    }

    return cost;
}

void C_AStar::SearchPath(void)
{
    UINT x, y, xm1, xp1, ym1, yp1;
    double minCost;

    list<pair<UINT, UINT> >::iterator elemWithMinCost, it;
    NodeState nodeState;

    FreeNodes();
    m_rawPath.clear();
    m_marginPath.clear();
    m_directPath.clear();
    matrixsChanges.clear();

    // Start or End out of map
    if (m_startNode.first > m_mapWidth || m_startNode.second > m_mapHeight) return;
    if (m_endNode.first > m_mapWidth || m_endNode.second > m_mapHeight) return;

    // Start or End in in a wall ... :-(
    if(m_nodesMatrix[m_startNode.first + m_startNode.second * m_mapWidth].type == WALLNODE) return;
    if(m_nodesMatrix[m_endNode.first + m_endNode.second * m_mapWidth].type == WALLNODE) return;

    if (m_startNode == m_endNode)
    {
        m_rawPath.push_front(m_startNode);
        m_marginPath.push_front(m_startNode);
        m_directPath.push_front(m_startNode);
        return;
    }

    openedNodes.clear();
    openedNodes.push_front(m_startNode);

    x = m_startNode.first;
    y = m_startNode.second;
    SetOriginNode(x, y, x, y);

    SearchNode * currentNode = m_nodesMatrix + y * m_mapWidth + x;
    currentNode->cost = 0;
    currentNode->pathCost = 0;
    currentNode->type = OPENEDNODE;
    currentNode->g = 0;

    // To prevent an infinit loop
    uint32_t iterationCounter = PATHFINDER_MAX_NB_ITER_OF_SEARCH_LOOP;

    SearchNode * endNodeInMatrix = m_nodesMatrix + m_endNode.first + m_endNode.second * m_mapWidth;

    // Exploration loop
    while (endNodeInMatrix->type != OPENEDNODE)
    {
        // Counter reachs 0
        if(!(iterationCounter--))
        {
            return;
        }

        minCost = numeric_limits<double>::max();

        if (openedNodes.size() == 0) return;

        // Search the min cost
        double checkCost;
        for (it = openedNodes.begin(); it != openedNodes.end(); it++)
        {
            if ((checkCost = m_nodesMatrix[it->first + it->second * m_mapWidth].cost) < minCost)
            {
                minCost = checkCost;
                elemWithMinCost = it;
            }
        }

        x = xm1 = xp1 = elemWithMinCost->first;
        xm1--;
        xp1++;
        y = ym1 = yp1 = elemWithMinCost->second;
        ym1--;
        yp1++;

        m_nodesMatrix [y * m_mapWidth + x].type = VISITEDNODE;

        openedNodes.remove(*elemWithMinCost);

        if (x > 0)
        {
            if (y > 0) OpenNode(xm1, ym1, x, y);

            OpenNode(xm1, y, x, y);

            if (yp1 < m_mapHeight)	OpenNode(xm1, yp1, x, y);
        }

        if (y > 0) OpenNode(x, ym1, x, y);

        if (yp1 < m_mapHeight) OpenNode(x, yp1, x, y);

        if (xp1 < m_mapWidth)
        {
            if (y > 0) OpenNode(xp1, ym1, x, y);

            OpenNode(xp1, y , x, y);

            if (yp1 < m_mapHeight)	OpenNode(xp1, yp1, x, y);
        }
    }

    // Build the raw path
    x = m_endNode.first;
    y = m_endNode.second;
    UINT x_plus_y_mapWidth = x + y * m_mapWidth;

    UINT x_origine = m_nodesMatrix[x_plus_y_mapWidth].originX;
    UINT y_origine = m_nodesMatrix[x_plus_y_mapWidth].originY;

    // From the end node to the start node
    while ((x_origine != x) || (y_origine != y))
    {
        m_rawPath.push_front(make_pair(x, y));
        x = x_origine;
        y = y_origine;

        x_plus_y_mapWidth = x + y * m_mapWidth;
        x_origine = m_nodesMatrix[x_plus_y_mapWidth].originX;
        y_origine = m_nodesMatrix[x_plus_y_mapWidth].originY;
    }

    // Start node
    m_rawPath.push_front(m_startNode);

    // Build the margin path
    m_marginPath = m_rawPath;
    AddMargin(m_marginPath, NAV_MAP_OBSTACLE_MARGIN_1_EXPAND_COST);
    RemoveDuplicatedNode(m_marginPath);
    RepopulatePath(m_marginPath);
    AddMargin(m_marginPath, NAV_MAP_OBSTACLE_MARGIN_2_EXPAND_COST);
    RemoveDuplicatedNode(m_marginPath);
    RepopulatePath(m_marginPath);


    // Build the direct path
    m_directPath = m_marginPath;
    FilterCloseTargets(m_directPath);
    FindDirectPath(m_directPath);
    FindDirectPath(m_directPath);

    return;
}

void C_AStar::SetMatrix(UINT width, UINT height)
{
    DestroyMatrix();

    this->m_mapWidth = width;
    this->m_mapHeight = height;

    if (width == 0 || height == 0) return;

    m_nodesMatrix = new SearchNode[width * height];
}

void C_AStar::SetStart(UINT x, UINT y)
{
    if (x <= m_mapWidth && y <= m_mapHeight)
    {
        m_startNode.first = x;
        m_startNode.second = y;
    }
}

void C_AStar::SetEnd(UINT x, UINT y)
{
    if (x <= m_mapWidth && y <= m_mapHeight)
    {
        m_endNode.first = x;
        m_endNode.second = y;
    }
}

void C_AStar::SetWall(UINT x, UINT y)
{
    //if		(m_nodesMatrix == NULL)			return;
    //else if	(x > m_mapWidth || y > m_mapHeight)	return;

    if(x > m_mapWidth || y > m_mapHeight)	return;
    m_nodesMatrix[x + y * m_mapWidth].type = WALLNODE;
}

void C_AStar::SetWay(UINT x, UINT y, UINT expandCost)
{
    //if		(m_nodesMatrix == NULL)			return;
    //else if	(x > m_mapWidth || y > m_mapHeight)	return;

    if(x > m_mapWidth || y > m_mapHeight)	return;
    m_nodesMatrix[x + y * m_mapWidth].type = WAYNODE;
    m_nodesMatrix[x + y * m_mapWidth].expandCost = expandCost;
}

void C_AStar::SetHeuristics(AStarHeuristics heuristic)
{
    if (heuristic >= none && heuristic <= newH)
    {
        this->heuristic = heuristic;
    }
    else
    {
        this->heuristic = euclidean;
    }
}

void C_AStar::DestroyMatrix()
{
    if (m_nodesMatrix != NULL)
    {
        UINT nbNodes = m_mapWidth * m_mapHeight;

        for (UINT i = 0; i < nbNodes; i++)
            delete (m_nodesMatrix + i);

        m_nodesMatrix = NULL;
    }

    m_rawPath.clear();
    m_marginPath.clear();
    m_directPath.clear();
    openedNodes.clear();
    matrixsChanges.clear();
}

NodeType C_AStar::GetNodeType(UINT x, UINT y) const
{
    //if		(m_nodesMatrix == NULL)			return NONE;
    //else if	(x > m_mapWidth || y > m_mapHeight)	return NONE;

    if(x > m_mapWidth || y > m_mapHeight)	return NONE;
    return m_nodesMatrix[x + y * m_mapWidth].type;
}

pair<UINT, UINT> C_AStar::GetStart() const
{
    return m_startNode;
}

pair<UINT, UINT> C_AStar::GetEnd() const
{
    return m_endNode;
}



list<list<NodeState> > C_AStar::getChanges() const
{
    return matrixsChanges;
}

double C_AStar::EtimateCost(UINT x1, UINT y1, UINT x2, UINT y2)
{
    double x_minus_destX = (double)x2 - (double)m_endNode.first;
    double y_minus_destY = (double)y2 - (double)m_endNode.second;

    double h = 0.0;

    if (heuristic == euclidean)             h = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
    else if (heuristic == manhattan)		h = abs(x_minus_destX) + abs(y_minus_destY);
    else if (heuristic == diagonal)			h = max(abs(x_minus_destX), abs(y_minus_destY));
    else if (heuristic == newH)
    {
        double euc = C_Tools_Maths::sqrt7(x_minus_destX * x_minus_destX + y_minus_destY * y_minus_destY);
        h = ceil(euc) - euc;
    }

    // return h + g
    return (h + (double)(m_nodesMatrix[x1 + y1 * m_mapWidth].g + m_nodesMatrix[x2 + y2 * m_mapWidth].expandCost));
}

void C_AStar::ClearPath(void)
{
    m_rawPath.clear();
    m_marginPath.clear();
    m_directPath.clear();
}


void C_AStar::AddMargin(list<pair<UINT, UINT>> & path, UINT maxCost)
{
    if(path.size() > 2)
    {
        // Ignore the first and the last
        list<pair<UINT, UINT> >::iterator pathIt = path.begin();
        list<pair<UINT, UINT> >::iterator lastIter = std::prev(path.end());

        pathIt++;
        // For each waypoint
        for (; pathIt != lastIter; pathIt++)
        {
            // New waypoint (if needed)
            int newX;
            int newY;

            // Need the dest waypoint to be moved
            if(FindAvoidanceIfIsTooCLosedToAnObstacle(pathIt->first, pathIt->second, maxCost, &newX, &newY))
            {
                *pathIt = make_pair(newX, newY);
            }
        }
    }
}

bool C_AStar::GetNextTarget(int currentPosX, int currentPosY, uint32_t *targetId, uint32_t *totalNbOfTargets, int *targetPosX, int *targetPosY, bool *isLastTarget)
{
    // From the simplified path, reconstruct the dense path
    // ============================================================================================
    m_marginPath = m_directPath;
    RepopulatePath(m_marginPath);

     // Review the path margin and the final direct path
    // ============================================================================================
    AddMargin(m_marginPath, NAV_MAP_OBSTACLE_MARGIN_1_EXPAND_COST);
    RemoveDuplicatedNode(m_marginPath);
    RepopulatePath(m_marginPath);
    AddMargin(m_marginPath, NAV_MAP_OBSTACLE_MARGIN_2_EXPAND_COST);
    RemoveDuplicatedNode(m_marginPath);
    RepopulatePath(m_marginPath);


    // Now we have the updated path, search the nearest node to the current position
    // ============================================================================================
    int32_t closestNodeIndex = 0;
    int32_t closestNodeDist_2 = INT32_MAX;

    int32_t iterationIndex = 0;

    // For each waypoint
    for (list<pair<UINT, UINT>>::iterator pathIt = m_marginPath.begin(); pathIt != m_marginPath.end(); pathIt++)
    {
        // Dist between the current position to the target
        int32_t dx = currentPosX - (int32_t)(pathIt->first);
        int32_t dy = currentPosY - (int32_t)(pathIt->second);
        int32_t dist_2 = dx * dx + dy * dy;

        // Found a closer target (or equal, but farther in the path)
        if(dist_2 <= closestNodeDist_2)
        {
            closestNodeIndex = iterationIndex;
            closestNodeDist_2 = dist_2;
        }

        iterationIndex++;
    }

    // Check if the reserved node on the new path is not so far from the current position
    if(closestNodeDist_2 > 5)
    {
         // The new path is so far from the current position
         // We better stop following the path and recompute the full path from the current position
         *targetId = 0;
         *totalNbOfTargets = 0;
         *targetPosX = currentPosX;
         *targetPosY = currentPosY;
         *isLastTarget = true;

         return false;
    }

    // Check the current path validity
    // ============================================================================================
    // No path or invalid path
    if(!IsMarginPathValid(closestNodeIndex, 10))
    {
        *targetId = 0;
        *totalNbOfTargets = 0;
        *targetPosX = currentPosX;
        *targetPosY = currentPosY;
        *isLastTarget = true;

        return false;
    }

    // We will use the closest node as target, so reserve it from elimination by the next steps
    pair<UINT, UINT> nodePosToReserve = *(std::next(m_marginPath.begin(), closestNodeIndex));

    // Compute the direct path keeping the reserved node
    m_directPath = m_marginPath;
    FilterCloseTargets(m_directPath, nodePosToReserve);
    FindDirectPath(m_directPath, nodePosToReserve);
    FindDirectPath(m_directPath, nodePosToReserve);

    // Get back the reserved node in the new simplified path
    // ============================================================================================
    list<pair<UINT, UINT>>::iterator targetIter = std::find(m_directPath.begin(), m_directPath.end(), nodePosToReserve);

    // The target is the last
    *isLastTarget = (targetIter == std::prev(m_directPath.end()));

    // Not the last, so take the next
    if(!(*isLastTarget))
    {
        targetIter++;
        *isLastTarget = (targetIter == std::prev(m_directPath.end()));
    }

    // Read data about the target
    *totalNbOfTargets = m_directPath.size();
    *targetId = std::distance(m_directPath.begin(), targetIter);
    *targetPosX = targetIter->first;
    *targetPosY = targetIter->second;

    return true;
}

bool C_AStar::RemoveDuplicatedNode(list<pair<UINT, UINT>> & path)
{
    if(path.size() > 0)
    {
        // Backup for process
        list<pair<UINT, UINT>> pathOriginal = path;

        // Clear for reconstruction
        path.clear();

        // Add one by one node to the new list when it is not already in the new list
        for (list<pair<UINT, UINT> >::iterator pathIt = pathOriginal.begin(); pathIt != pathOriginal.end(); pathIt++)
        {
            // The node is not in the new list
            if(std::find(path.begin(), path.end(), *pathIt) == path.end())
            {
                path.push_back(*pathIt);
            }
        }

        return true;
    }

    return false;
}


bool C_AStar::IsMarginPathValid(int startNodeIndex, int distToCheck)
{
    float cumulCheckedDist = 0;

    // No path, the path is invalid
    if(m_marginPath.size() > startNodeIndex)
    {
        // Look at each waypoint and check if it is still valid
        // Not on a wall

        list<pair<UINT, UINT> >::iterator pathIt = (std::next(m_marginPath.begin(), startNodeIndex));
        float lastX = pathIt->first;
        float lastY = pathIt->second;

        pathIt++;
        for (; pathIt != m_marginPath.end(); pathIt++)
        {
            int currentX = pathIt->first;
            int currentY = pathIt->second;

            // Oups, wall !!
            if(m_nodesMatrix[currentX + currentY * m_mapWidth].type == WALLNODE)
            {
                return false;
            }

            float dx = lastX - currentX;
            float dy = lastY - currentY;

            if((cumulCheckedDist += C_Tools_Maths::sqrt7(dx * dx + dy * dy)) >= distToCheck) break;

            lastX = currentX;
            lastY = currentY;
        }

        return true;
    }

    return false;
}


bool C_AStar::IsInLineOfSight(int x0, int y0, int x1, int y1)
{
    int diffX = x1 - x0;
    int diffY = y1 - y0;

    int f = 0;

    int dirX = 1;
    int dirY = 1;

    if (diffY < 0)
    {
        diffY = -diffY;
        dirY = -1;
    }

    int dirY_x_mapWidth = dirY * m_mapWidth;
    int y0_x_mapWidth = y0 * m_mapWidth;

    if (diffX < 0)
    {
        diffX = -diffX;
        dirX = -1;
    }

    if (diffX >= diffY)
    {
        // Move along the x axis and increment/decrement y when f >= diff.x.
        while(true)
        {
            // Oups, wall !!
            if(m_nodesMatrix[x0 + y0_x_mapWidth].type == WALLNODE)
            {
                return false;
            }

            // Oups, expand cost is bigger
            if(m_nodesMatrix[x0 + y0_x_mapWidth].expandCost > NAV_MAP_NO_OBSTACLE_EXPAND_COST)
            {
                return false;
            }

            if(x0 == x1) break;

            // Compute next point to check
            if ((f += diffY) >= diffX)
            {
                y0 += dirY;
                y0_x_mapWidth += dirY_x_mapWidth;

                f -= diffX;
            }

            x0 += dirX;
        }
    }
    else
    {
        //if (diff.x < diff.y). Move along the y axis and increment/decrement x when f >= diff.y.
        while(true)
        {
            // Oups, wall !!
            if(m_nodesMatrix[x0 + y0_x_mapWidth].type == WALLNODE)
            {
                return false;
            }

            // Oups, expand cost is bigger
            if(m_nodesMatrix[x0 + y0_x_mapWidth].expandCost > NAV_MAP_NO_OBSTACLE_EXPAND_COST)
            {
                return false;
            }

            if(y0 == y1) break;

            // Compute next point to check
            if ((f += diffX) >= diffY)
            {
                x0 += dirX;
                f -= diffY;
            }

            y0 += dirY;
            y0_x_mapWidth += dirY_x_mapWidth;
        }
    }

    return true;
}


void C_AStar::FindDirectPath(list<pair<UINT, UINT>> & path)
{
    // We can not be more direct when there are less than 2 points
    if(path.size() > 2)
    {
        // Path iterator
        list<pair<UINT, UINT> >::iterator pathIt = path.begin();

        // First point
        pair<UINT, UINT> lastSmoothNode = *pathIt;
        UINT lastSmoothNodeExpandCost = m_nodesMatrix[lastSmoothNode.first + lastSmoothNode.second * m_mapWidth].expandCost;

        // Second point
        pathIt++;
        list<pair<UINT, UINT> >::iterator lastNodeIter = pathIt;

        // Move to the next node
        pathIt++;

        // Now look for each next point if we need delete or keep
        for (; pathIt != path.end(); pathIt++)
        {
            // Check if the new point has direct sight
            if(IsInLineOfSight(lastSmoothNode.first, lastSmoothNode.second, pathIt->first, pathIt->second))
            {
                // Yes, so the intermediate point is useless
                path.erase(lastNodeIter);
            }
            else
            {
                // No direct sight, so keep the last point
                lastSmoothNode = *lastNodeIter;
                lastSmoothNodeExpandCost = m_nodesMatrix[lastSmoothNode.first + lastSmoothNode.second * m_mapWidth].expandCost;
            }

            lastNodeIter = pathIt;
        }
    }
}

void C_AStar::FindDirectPath(list<pair<UINT, UINT>> & path, pair<UINT, UINT> reservedPos)
{
    // We can not be more direct when there are less than 2 points
    if(path.size() > 2)
    {
        // Path iterator
        list<pair<UINT, UINT> >::iterator pathIt = path.begin();

        // First point
        pair<UINT, UINT> lastSmoothNode = *pathIt;
        UINT lastSmoothNodeExpandCost = m_nodesMatrix[lastSmoothNode.first + lastSmoothNode.second * m_mapWidth].expandCost;

        // Second point
        pathIt++;
        list<pair<UINT, UINT> >::iterator lastNodeIter = pathIt;
        pair<UINT, UINT> lastNode = *lastNodeIter;


        // Move to the next node
        pathIt++;

        // Now look for each next point if we need delete or keep
        for (; pathIt != path.end(); pathIt++)
        {
            pair<UINT, UINT> currentNode = *pathIt;

            // Check if the new point has direct sight and not reserved position
            if((lastNode != reservedPos) && IsInLineOfSight(lastSmoothNode.first, lastSmoothNode.second, currentNode.first, currentNode.second))
            {
                // Yes, so the intermediate point is useless
                path.erase(lastNodeIter);
            }
            else
            {
                // No direct sight, so keep the last point
                lastSmoothNode = lastNode;
                lastSmoothNodeExpandCost = m_nodesMatrix[lastSmoothNode.first + lastSmoothNode.second * m_mapWidth].expandCost;
            }

            lastNodeIter = pathIt;
            lastNode = *lastNodeIter;
        }
    }
}


void C_AStar::FilterCloseTargets(list<pair<UINT, UINT>> & path)
{
    if(path.size() > 2)
    {
        // Backup for process
        list<pair<UINT, UINT>> pathOriginal = path;

        // Clear for reconstruction
        path.clear();

        // Path iterator
        list<pair<UINT, UINT>>::iterator pathIt = pathOriginal.begin();
        pair<UINT, UINT> lastNode = *pathIt;

        // Save the first node
        path.push_back(lastNode);

        // Save the last node
        list<pair<UINT, UINT> >::iterator lastIter = std::prev(pathOriginal.end());

        // Move to the next node
        pathIt++;

        // Now look for each next point if we need delete or keep
        for (; pathIt != lastIter; pathIt++)
        {
            pair<UINT, UINT> currentNode = *pathIt;

            int dx = currentNode.first - lastNode.first;
            if (dx < 0) dx = -dx;
            int dy = currentNode.second - lastNode.second;
            if (dy < 0) dy = -dy;

            if((dx > 2) || (dy > 2))
            {
                lastNode = *pathIt;
                path.push_back(lastNode);
            }
        }

        // Save the last node
        path.push_back(*pathIt);
    }
}


void C_AStar::FilterCloseTargets(list<pair<UINT, UINT>> & path, pair<UINT, UINT> reservedPos)
{
    if(path.size() > 2)
    {
        // Backup for process
        list<pair<UINT, UINT>> pathOriginal = path;

        // Clear for reconstruction
        path.clear();

        // Path iterator
        list<pair<UINT, UINT>>::iterator pathIt = pathOriginal.begin();
        pair<UINT, UINT> lastNode = *pathIt;

        // Save the first node
        path.push_back(lastNode);

        // Save the last node
        list<pair<UINT, UINT> >::iterator lastIter = std::prev(pathOriginal.end());

        // Move to the next node
        pathIt++;

        // Now look for each next point if we need delete or keep
        for (; pathIt != lastIter; pathIt++)
        {
            pair<UINT, UINT> currentNode = *pathIt;

            if(currentNode != reservedPos)
            {
                int dx = currentNode.first - lastNode.first;
                if (dx < 0) dx = -dx;
                int dy = currentNode.second - lastNode.second;
                if (dy < 0) dy = -dy;

                if((dx > 2) || (dy > 2))
                {
                    lastNode = *pathIt;
                    path.push_back(lastNode);
                }
            }
            else
            {
                lastNode = *pathIt;
                path.push_back(lastNode);
            }
        }

        // Save the last node
        path.push_back(*pathIt);
    }
}


// Return True if has neighbour
// Also return the opposite point to go away from the neighbour
bool C_AStar::IsTooCLosedToAnObstacle(int x, int y, UINT maxCost)
{
    // For optimization, precompute neighnour coordinates
    int xp1 = x + 1;
    int xm1 = x - 1;
    int yp1 = y + 1;
    int ym1 = y - 1;

    // Precompute access to the map
    int ym1_width = ym1 * m_mapWidth;
    int y_width = y * m_mapWidth;
    int yp1_width = yp1 * m_mapWidth;

    // Protection
    if((xm1 < 0) || (xp1 >= (int)m_mapWidth) || (ym1 < 0) || (yp1 >= (int)m_mapHeight)) return false;

    if((m_nodesMatrix[xm1 + ym1_width].type == WALLNODE) || (m_nodesMatrix[xm1 + ym1_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[xm1 + y_width].type == WALLNODE) || (m_nodesMatrix[xm1 + y_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[xm1 + yp1_width].type == WALLNODE) || (m_nodesMatrix[xm1 + yp1_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[x + ym1_width].type == WALLNODE) || (m_nodesMatrix[x + ym1_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[x + yp1_width].type == WALLNODE) || (m_nodesMatrix[x + yp1_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[xp1 + ym1_width].type == WALLNODE) || (m_nodesMatrix[xp1 + ym1_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[xp1 + y_width].type == WALLNODE) || (m_nodesMatrix[xp1 + y_width].expandCost >= maxCost))
    {
        return true;
    }
    if((m_nodesMatrix[xp1 + yp1_width].type == WALLNODE) || (m_nodesMatrix[xp1 + yp1_width].expandCost >= maxCost))
    {
        return true;
    }

    return false;
}


// Return True if has neighbour
// Also return the opposite point to go away from the neighbour
bool C_AStar::FindAvoidanceIfIsTooCLosedToAnObstacle(int x, int y, UINT maxCost, int *avoidNeighbourX, int *avoidNeighbourY)
{
    // For optimization, precompute neighnour coordinates
    int xp1 = x + 1;
    int xm1 = x - 1;
    int yp1 = y + 1;
    int ym1 = y - 1;

    // Precompute access to the map
    int ym1_width = ym1 * m_mapWidth;
    int y_width = y * m_mapWidth;
    int yp1_width = yp1 * m_mapWidth;

    // Avoidance direction
    int chargeX = 0;
    int chargeY = 0;

    // Protection
    if((xm1 < 0) || (xp1 >= (int)m_mapWidth) || (ym1 < 0) || (yp1 >= (int)m_mapHeight)) return false;

    bool foundCLosedObstacle = false;

    if((m_nodesMatrix[xm1 + ym1_width].type == WALLNODE) || (m_nodesMatrix[xm1 + ym1_width].expandCost >= maxCost))
    {
        chargeX++;
        chargeY++;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[xm1 + y_width].type == WALLNODE) || (m_nodesMatrix[xm1 + y_width].expandCost >= maxCost))
    {
        chargeX++;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[xm1 + yp1_width].type == WALLNODE) || (m_nodesMatrix[xm1 + yp1_width].expandCost >= maxCost))
    {
        chargeX++;
        chargeY--;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[x + ym1_width].type == WALLNODE) || (m_nodesMatrix[x + ym1_width].expandCost >= maxCost))
    {
        chargeY++;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[x + yp1_width].type == WALLNODE) || (m_nodesMatrix[x + yp1_width].expandCost >= maxCost))
    {
        chargeY--;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[xp1 + ym1_width].type == WALLNODE) || (m_nodesMatrix[xp1 + ym1_width].expandCost >= maxCost))
    {
        chargeX--;
        chargeY++;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[xp1 + y_width].type == WALLNODE) || (m_nodesMatrix[xp1 + y_width].expandCost >= maxCost))
    {
        chargeX--;
        foundCLosedObstacle = true;
    }
    if((m_nodesMatrix[xp1 + yp1_width].type == WALLNODE) || (m_nodesMatrix[xp1 + yp1_width].expandCost >= maxCost))
    {
        chargeX--;
        chargeY--;
        foundCLosedObstacle = true;
    }

    // If need to return a solution
    // So check the new point has no closed obstacle
    if(foundCLosedObstacle)
    {
        if(chargeX > 0) *avoidNeighbourX = x + 1;
        else if(chargeX < 0) *avoidNeighbourX = x - 1;
        else *avoidNeighbourX = x;

        if(chargeY > 0) *avoidNeighbourY = y + 1;
        else if(chargeY < 0) *avoidNeighbourY = y - 1;
        else *avoidNeighbourY = y;

        // The solution is safer than the current point
        int neighbourTabIndex = (*avoidNeighbourX) + (*avoidNeighbourY) * m_mapWidth;

        // Solution is a wall : not OK
        if(m_nodesMatrix[neighbourTabIndex].type == WALLNODE) return false;

        // Solution is lower cost : OK
        if (m_nodesMatrix[neighbourTabIndex].expandCost < m_nodesMatrix[x + y_width].expandCost) return true;

        foundCLosedObstacle = !IsTooCLosedToAnObstacle(*avoidNeighbourX, *avoidNeighbourY, maxCost);
    }

    return foundCLosedObstacle;
}

void C_AStar::RepopulatePath(list<pair<UINT, UINT>> & path)
{
    if(path.size() > 0)
    {
        // Nodes iterator
        list<pair<UINT, UINT> >::iterator pathIt = path.begin();

        // Start point of the next section of path to study
        int x0 = pathIt->first;
        int y0 = pathIt->second;

        // Move to the next node
        pathIt++;

        // For each waypoint
        for (; pathIt != path.end(); pathIt++)
        {
            list<pair<UINT, UINT> > pathSegment;
            CreatePathSegment(x0, y0, pathIt->first, pathIt->second, pathSegment);

            if(pathSegment.size() > 0)
            {
                path.insert(pathIt,pathSegment.begin(), pathSegment.end());
            }

            x0 = pathIt->first;
            y0 = pathIt->second;
        }
    }
}

bool C_AStar::CreatePathSegment(int x0, int y0, int x1, int y1, list<pair<UINT, UINT>> & pathSegment)
{
    pathSegment.clear();

    int diffX = x1 - x0;
    int diffY = y1 - y0;

    int f = 0;

    int dirX = 1;
    int dirY = 1;

    if (diffY < 0)
    {
        diffY = -diffY;
        dirY = -1;
    }

    if (diffX < 0)
    {
        diffX = -diffX;
        dirX = -1;
    }

    if (diffX >= diffY)
    {
        // Move along the x axis and increment/decrement y when f >= diff.x.
        while((x0 != x1))
        {
            // Compute next point to check
            if ((f += diffY) >= diffX)
            {
                y0 += dirY;
                f -= diffX;
            }

            x0 += dirX;
            if(x0 != x1) pathSegment.push_back(make_pair(x0,y0));
        }
    }
    else
    {
        //if (diff.x < diff.y). Move along the y axis and increment/decrement x when f >= diff.y.
        while(y0 != y1)
        {
            // Compute next point to check
            if ((f += diffX) >= diffY)
            {
                x0 += dirX;
                f -= diffY;
            }

            y0 += dirY;
            if(y0 != y1) pathSegment.push_back(make_pair(x0,y0));
        }
    }

    return true;
}







