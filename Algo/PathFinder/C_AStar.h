#ifndef NULL
#define NULL 0
#endif

#ifndef UINT
#define UINT unsigned int
#endif


#ifndef ASTAR_H_
#define ASTAR_H_

#include <list>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>

#include "constants.h"
#include "C_Tools_Maths.h"

using namespace std;

enum ToSetState
{
    TOSETWALL,
    TOSETWAY,
    TOSETDIRT,
    TOSETSTART,
    TOSETEND
};

enum NodeType
{
    NONE = 0,
    WAYNODE,
    WALLNODE,
    OPENEDNODE,
    VISITEDNODE
};

enum AStarHeuristics
{
    none,
    euclidean,
    manhattan,
    diagonal,
    newH
};

enum AncestorDirection
{
    SELF,
    UPLEFT,
    UP,
    UPRIGHT,
    LEFT,
    RIGHT,
    DOWNLEFT,
    DOWN,
    DOWNRIGHT
};

class SearchNode
{

public:

    NodeType type;

    UINT originX;
    UINT originY;
    double h;
    UINT g;
    UINT expandCost;
    double cost;
    double pathCost;

    SearchNode();
    ~SearchNode();
};

class PathNode
{

public:

    UINT x;
    UINT y;

    PathNode();
    ~PathNode();
};

class NodeState
{

public:

    UINT x;
    UINT y;

    NodeType state;

    AncestorDirection ancestor;

    NodeState();
    NodeState(UINT x, UINT y, NodeType state);
    ~NodeState();
};


enum AStarPathType
{
    raw,
    direct,
    margin
};


class C_AStar
{
    SearchNode * m_nodesMatrix;

    UINT m_mapWidth;
    UINT m_mapHeight;
    pair<UINT, UINT> m_startNode;
    pair<UINT, UINT> m_endNode;

    list<pair<UINT, UINT> > m_rawPath;
    list<pair<UINT, UINT> > m_marginPath;
    list<pair<UINT, UINT> > m_directPath;
    list<pair<UINT, UINT> > openedNodes;
    list<list<NodeState> > matrixsChanges;

    AStarHeuristics heuristic;

    bool ready;

    void ComputeCost(pair<UINT, UINT> node);
    void OpenNode(UINT x, UINT y, UINT originX, UINT originY);
    void FreeNodes();
    void SetOriginNode(UINT x, UINT y, UINT originX, UINT originY);
    double PathCostToNode(UINT x, UINT y, UINT destX, UINT destY);


    bool RemoveDuplicatedNode(list<pair<UINT, UINT>> & path);

    // Try to go in direct line instead of surrounding path
    // But the line shall respect the cost constraints
    void FindDirectPath(list<pair<UINT, UINT>> & path);
    // Find a direct like FindDirectPath2() but force reserve the given waypoint
    void FindDirectPath(list<pair<UINT, UINT>> & path, pair<UINT, UINT> reservedPos);

    // Remove points too closed together
    void FilterCloseTargets(list<pair<UINT, UINT>> & path);
    void FilterCloseTargets(list<pair<UINT, UINT>> & path, pair<UINT, UINT> reservedPos);


    // Check if every point on the line from (x0,y0) to (x1,y1) are completely free
    bool IsInLineOfSight(int x0, int y0, int x1, int y1);

    // Add margin to point which has neigbour equal or bigger than maxCost
    void AddMargin(list<pair<UINT, UINT>> & path, UINT maxCost);

    // Try to find avoidance solution for a point which has neigbour equal or bigger than maxCost
    bool FindAvoidanceIfIsTooCLosedToAnObstacle(int x, int y, UINT maxCost, int *avoidNeighbourX, int *avoidNeighbourY);

    // Check if a point is near an other with equal or bigger than maxCost
    bool IsTooCLosedToAnObstacle(int x, int y, UINT maxCost);

    // Add all intermediat points from a given path
    void RepopulatePath(list<pair<UINT, UINT>> & path);
    // Create a segment of path with all intermediat points
    bool CreatePathSegment(int x0, int y0, int x1, int y1, list<pair<UINT, UINT>> & pathSegment);

public:

    C_AStar();
    C_AStar(UINT m_mapWidth, UINT m_mapHeight);
    ~C_AStar();

    bool GetNextTarget(int currentPosX, int currentPosY, uint32_t *targetId, uint32_t *totalNbOfTargets, int *targetPosX, int *targetPosY, bool *isLastTarget);

    void SetMatrix(UINT m_mapWidth, UINT m_mapHeight);
    void SetStart(UINT x, UINT y);
    void SetEnd(UINT x, UINT y);
    void SetWall(UINT x, UINT y);
    void SetWay(UINT x, UINT y, UINT expandCost = 1);
    void SetHeuristics(AStarHeuristics heuristic);

    NodeType GetNodeType(UINT x, UINT y) const;
    pair<UINT, UINT> GetStart() const;
    pair<UINT, UINT> GetEnd() const;
    list<list<NodeState> > getChanges() const;

    double EtimateCost(UINT x1, UINT y1, UINT x2, UINT y2);

    void DestroyMatrix();

    void SearchPath(void);

    list<pair<UINT, UINT> > GetPath(AStarPathType getPathType)
    {
        switch(getPathType)
        {
        case AStarPathType::raw:
            return m_rawPath;
        case AStarPathType::margin:
            return m_marginPath;
        case AStarPathType::direct:
            return m_directPath;
        default:
            break;
        }

        return m_rawPath;
    }

    void ClearPath(void);
    bool IsMarginPathValid(int startNodeIndex, int distToCheck);
    bool CheckNextWayPointsNotGoingIntoObstacle(list<pair<UINT, UINT>> m_rawPath, int x0, int y0, int startWaypointIndex, int maxDistToCheck__pixel);
};

#endif
