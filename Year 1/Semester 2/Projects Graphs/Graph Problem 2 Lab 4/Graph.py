from copy import deepcopy
from queue import Queue
from collections import deque


class GraphException(Exception):
    def __init__(self, m):
        super().__init__(m)


class Graph:
    def __init__(self, n):
        """
        Constructor for the Graph class
        Creates an empty graph with n vertices
        Precondition: n must be a positive integer
        :param n: Number of vertices to have as default
        raises GraphException if n is not a positive number or 0 (n>0)
        """
        if n < 0:
            raise GraphException("Invalid number of vertices")

        self._dictIn = {}
        self._dictOut = {}
        self._dictCost = {}

        self._vertexCost = {}
        for i in range(0, n):
            self._dictIn[i] = []
            self._dictOut[i] = []

    def add_vertex_cost(self, x, cost):
        self._vertexCost[x] = cost

    def get_vertex_cost(self, x):
        return self._vertexCost[x]

    def get_number_of_vertices(self):
        """
        Gets the number of vertices
        :return: the number of vertices
        """
        return len(self._dictIn.keys())

    def parse_vertices(self):
        """
        Returns an iterator for the vertices
        :return: an iterator for the vertices
        """
        return iter(self._dictIn.keys())

    def edge_exists(self, x, y):
        """
        Checks if an edge exists
        Precondition: x and y need to be valid vertices
        :param x: The source
        :param y: The target
        :return: True if it exists, false otherwise
        raises GraphException if x or y is an invalid vertex
        """
        if x not in self._dictIn.keys() or y not in self._dictIn.keys():
            raise GraphException("Invalid vertex")

        if (x, y) in self._dictCost.keys():
            return True
        else:
            return False

    def get_in_degree(self, x):
        """
        Gets the in degree of vertex x
        Precondition: x must be a valid vertex
        :param x: The vertex
        :return: An integer representing the in degree of the vertex
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictIn.keys():
            raise GraphException("Invalid vertex")

        return len(self._dictIn[x])

    def get_out_degree(self, x):
        """
        Gets the out degree of vertex x
        Precondition: x must be a valid vertex
        :param x: The vertex
        :return: An integer representing the out degree of the vertex
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictIn.keys():
            raise GraphException("Invalid vertex")

        return len(self._dictOut[x])

    def parse_outbound_edges(self, x):
        """
        Creates an iterator that goes trough the targets of the outbound edges having the source x
        Precondition: x must be a valid vertex
        :param x: The x vertex
        :return: An iterator for the outbound edges with x as a source
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictIn.keys():
            raise GraphException("Invalid vertex")

        return iter(self._dictOut[x])

    def parse_inbound_edges(self, x):
        """
        Creates an iterator that goes trough the sources of the inbound edges having the target x
        Precondition: x must be a valid vertex
        :param x: The x vertex
        :return: An iterator for the inbound edges with x as a target
        raises GraphException if x is not a valid vertex
        """
        if x not in self._dictIn.keys():
            raise GraphException("Invalid vertex")

        return iter(self._dictIn[x])

    def get_cost_of_edge(self, x, y):
        """
        Gets the cost of an edge
        Precondition: x and y must be valid vertices and (x, y) a valid edge
        :param x: Source
        :param y: Target
        :return: An integer representing the cost of an edge
        raises GraphException for x, y no valid vertices or (x, y) not a valid edge
        """
        if (x, y) not in self._dictCost.keys():
            raise GraphException("Edge doesn't exists!")

        if x not in self._dictIn.keys() or y not in self._dictIn.keys():
            raise GraphException("Invalid vertices!")

        return self._dictCost[(x, y)]

    def modify_cost_of_edge(self, x, y, c):
        """
        Modifies the cost of an edge
        Precondition: x and y must be valid vertices and (x, y) a valid edge
        :param x: Source
        :param y: Target
        :param c: New cost
        :return: -
        raises GraphException for x, y no valid vertices or (x, y) not a valid edge
        """
        if (x, y) not in self._dictCost.keys():
            raise GraphException("Edge doesn't exists!")

        if x not in self._dictIn.keys() or y not in self._dictIn.keys():
            raise GraphException("Invalid vertices!")

        self._dictCost[(x, y)] = c

    def add_edge(self, x, y, c):
        """
        Adds a new edge
        Precondition: valid x, y vertices and the edge shouldn't exist already
        :param x: Source
        :param y: Target
        :param c: Cost
        :return: -
        raises GraphException if the vertices are invalid or the edge already exists
        """
        if (x, y) in self._dictCost.keys():
            raise GraphException("Edge already exists!")

        if x not in self._dictIn.keys() or y not in self._dictIn.keys():
            raise GraphException("Invalid vertices!")

        self._dictOut[x].append(y)
        self._dictIn[y].append(x)
        self._dictCost[(x, y)] = c

    def remove_edge(self, x, y):
        """
        Removes an edge
        Precondition: valid x, y vertices and the edge should exist
        :param x: Source
        :param y: Target
        :return: -
        raises GraphException if the vertices are incorrect or the edge doesnt exist
        """
        if x not in self._dictIn.keys() or y not in self._dictIn.keys():
            raise GraphException("Invalid vertices!")

        if (x, y) not in self._dictCost.keys():
            raise GraphException("Edge doesnt exist!")

        self._dictOut[x].remove(y)
        self._dictIn[y].remove(x)
        del self._dictCost[(x, y)]

    def add_vertex(self, x):
        """
        Adds a new vertex
        Precondition: the vertex shouldn't already exist
        :param x: The vertex to be added
        :return: -
        raises GraphException if the vertex already exists or if it s a negative one
        """
        if x in self._dictIn.keys():
            raise GraphException("Vertex already exists!")

        self._dictIn[x] = []
        self._dictOut[x] = []

    def remove_vertex(self, x):
        """
        Removes the vertex x
        Precondition: x must be a valid vertex
        :param x: A vertex
        :return: -
        raises GraphException if the vertex doesn't exist
        """
        if x not in self._dictIn.keys():
            raise GraphException("Vertex doesn't exist")

        # deleting the vertex from the out dict and costs
        for v in self._dictIn[x]:
            self._dictOut[v].remove(x)
            del self._dictCost[(v, x)]

        # deleting the vertex from the in dict and costs
        for v in self._dictOut[x]:
            self._dictIn[v].remove(x)
            del self._dictCost[(x, v)]

        del self._dictIn[x]
        del self._dictOut[x]

    def get_copy_of_graph(self):
        """
        Creates a deepcopy of the graph and returns it
        :return: A deepcopy of the currnt graph
        """
        return deepcopy(self)

    def to_string(self):
        """
        Constructs and returns the string representation of the graph
        :return: string representation of the graph
        """
        return "In: " + str(self._dictIn) + "\n" + "Out: " + str(self._dictOut) + "\n" + "Costs: " + str(
            self._dictCost) + "\n"

    def sort_topological(self):
        sorted_list = []
        q = deque()
        count = {}

        # intialising count with
        for vertex in self._dictIn.keys():
            count[vertex] = self.get_in_degree(vertex)
            if count[vertex] == 0:
                q.append(vertex)

        while len(q) != 0:
            x = q.pop()
            sorted_list.append(x)
            for y in self.parse_outbound_edges(x):
                count[y] = count[y] - 1
                if count[y] == 0:
                    q.append(y)

        if len(sorted_list) < len(self._dictIn.keys()):
            raise GraphException("The graph contains a cycle, meaning it's not a DAG.\n")

        return sorted_list



        # sorted_list = []
        # q = Queue()
        # count = {}
        #
        # # intialising count with
        # for vertex in self._dictIn.keys():
        #     count[vertex] = self.get_in_degree(vertex)
        #     if count[vertex] == 0:
        #         q.put(vertex)
        #
        # while not q.empty():
        #     x = q.get()
        #     sorted_list.append(x)
        #     for y in self.parse_outbound_edges(x):
        #         count[y] = count[y] - 1
        #         if count[y] == 0:
        #             q.put(y)
        #
        # if len(sorted_list) < len(self._dictIn.keys()):
        #     raise GraphException("The graph contains a cycle, meaning it's not a DAG.\n")
        #
        # return sorted_list

    def calculate_times(self, sorted_list):
        time_list = {}

        for x in sorted_list:
            # 1st position is the most earliest time, second the latest earliest time that the activity begins
            # 3rd the cost of the activity, 4th the finishing time for the most earliest beginning time
            # 5th the finish time for the latest earliest time that the activity can begin
            time_list[x] = [0, 0, self.get_vertex_cost(x), 0, 0]

        for i in range(1, len(sorted_list)):
            x = sorted_list[i]
            # calculating the maximum from the in vertices
            maximum = -1
            for y in self.parse_inbound_edges(x):
                if maximum == -1:
                    maximum = time_list[y][3]
                else:
                    if maximum < time_list[y][3]:
                        maximum = time_list[y][3]

            time_list[x][0] = maximum
            time_list[x][3] = maximum + self.get_vertex_cost(x)

        #finding the latest time that it can start
        last_vertex = sorted_list[len(sorted_list)-1]
        time_list[last_vertex][4] = time_list[last_vertex][3]
        time_list[last_vertex][1] = time_list[last_vertex][4] - self.get_vertex_cost(last_vertex)

        for i in range(len(sorted_list)-2, -1, -1):
            x = sorted_list[i]
            # calculating the minimum from the in vertices
            minimum = -1
            for y in self.parse_outbound_edges(x):
                if minimum == -1:
                    minimum = time_list[y][1]
                else:
                    if minimum > time_list[y][1]:
                        minimum = time_list[y][1]
            time_list[x][4] = minimum
            time_list[x][1] = minimum - self.get_vertex_cost(x)

        return time_list


