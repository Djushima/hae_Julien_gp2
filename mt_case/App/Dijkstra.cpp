#include "Dijkstra.hpp"

void Dijkstra::init(const std::vector<Vector2f>& graph, const Vector2f& _start)
{
	G = graph;
	start = _start;
	for (const Vector2f& vec : graph) /*(int i = 0; i < graph.size(); i++)*/
	{
		distance[vec] = INFINITY;	/*distance[graph[i]] = INFINITY*/
	}
	distance[start] = 0;
}

Vector2f Dijkstra::findMin(const std::vector<Vector2f>& queue)
{
	double mini = INFINITY;
	Vector2f sommet = Vector2f(-1, -1);
	for (const Vector2f& vec : queue)
	{
		if (distance[vec] < mini)
		{
			mini = distance[vec];
			sommet = vec;
		}

	}
	return sommet;
}

int Dijkstra::findMin2(std::vector<Vector2f>& queue)
{
	double mini = INFINITY;
	int vtx = -1;
	for (int i = 0; i < queue.size(); ++i) {
		const Vector2f& vec = queue[i];
		if (distance[vec] < mini) {
			mini = distance[vec];
			vtx = i;
		}
	}
	return vtx;
}

double Dijkstra::weight(const Vector2f & a, const Vector2f & b)
{
	Vector2f diff = b - a;
	return sqrt((diff.x*diff.x + diff.y*diff.y));
}

void Dijkstra::maj_distance(const Vector2f & s1, const Vector2f & s2)
{
	if (distance[s2] > distance[s1] + weight(s1, s2))
	{
		distance[s2] = distance[s1] + weight(s1, s2);
		pred[s2] = s1;
	}
}

void Dijkstra::compute(const std::vector<Vector2f>& graph, const Vector2f & start) {
	init(graph, start);
	std::vector<Vector2f> Q = graph;

	while (Q.size() > 0)
	{
		/*Vector2f s1 = findMin(Q);
		int index = 0;
		while (Q[index] != s1)
		{
			index++;
		}
		Q.erase(Q.begin() + index);*/
		int sai = findMin2(Q);
		Vector2f sa = Q[sai];
		Q.erase(Q.begin() + sai);
		for (const Vector2f & s : Q) {
			if ((s.x == sa.x + 1 && s.y == sa.y)
				|| (s.x == sa.x - 1 && s.y == sa.y)
				|| (s.x == sa.x  && s.y == sa.y + 1)
				|| (s.x == sa.x  && s.y == sa.y - 1))
				maj_distance(sa, s);
		}
	}
	computed = true;
}

bool Dijkstra::FindPath(std::vector<Vector2f>& result, const Vector2f & end) {
	result.clear();
	Vector2f cur = end;
	while (cur != start) {
		result.push_back(cur);
		Vector2f prev = cur;
		cur = pred[cur];
		if (prev == cur)
			return false;
	}
	if (result.size() == 0) {
		return false;
	}
	else {
		result.push_back(start);
		std::reverse(result.begin(), result.end());
		return true;
	}
}
