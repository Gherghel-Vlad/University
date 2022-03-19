import random
from pathlib import Path

from Graph import *


class UIException(Exception):
    def __init__(self, m):
        super().__init__(m)


class UI:
    def __init__(self):
        self._graph = Graph(0)
        self._filename = "graph.txt"
        self._ex_filename = "graph.txt"

    def print_file_menu(self):
        print("\nCommands:")
        print("1 Read from file")
        print("2 Generate graph")
        print("3 Generate graph in random_graph1.txt and random_graph2.txt")
        print("4 Read table file")
        print("0 Exit\n")

    def print_graph_menu(self):
        print("\nCommands:")
        print("1 Show graph")
        print("2 Get number of vertices")
        print("3 Edge exists")
        print("4 Get in degree of vertex")
        print("5 Get out degree of vertex")
        print("6 Get the outbound edges of a vertex")
        print("7 Get the inbound edges of a vertex")
        print("8 Get cost of an edge")
        print("9 Modify the cost of an edge")
        print("10 Add edge")
        print("11 Remove edge")
        print("12 Add vertex")
        print("13 Remove vertex")
        print("14 Save")
        print("15 Sort topological and show the extra stuff regarding scheduling")
        print("0 Exit\n")

    def start_file_menu(self):
        done = False

        while not done:
            self.print_file_menu()
            command = input("Give command: ").strip()
            try:
                if command == "1":
                    self.read_from_file()
                    done = True
                    self.start_graph_menu()
                elif command == "2":
                    try:
                        n = int(input("Number of vertices: ").strip())
                        m = int(input("Number of edges: ").strip())
                    except ValueError:
                        raise UIException("Bad input!")
                    self._filename = "random.txt"
                    self.generate_graph(n, m)
                    self.save_graph_to_file()
                elif command == "3":
                    self.generate_graph(7, 20)
                    self._filename = "random_graph1.txt"
                    self.save_graph_to_file()
                    self.generate_graph(6, 40)
                    self._filename = "random_graph2.txt"
                    self.save_graph_to_file()
                elif command == "4":
                    self.read_table_from_file_ui()
                    self.start_graph_menu()
                elif command == "0":
                    done = True
                else:
                    print("Bad command!\n")
                print("Command ran successfully!")
            except Exception as e:
                print("Error: " + str(e))

    def start_graph_menu(self):
        done = False

        while not done:
            self.print_graph_menu()
            command = input("Give command: ").strip()
            try:
                if command == "1":
                    print(self._graph.to_string())
                elif command == "2":
                    print(f"Number of vertices: {self._graph.get_number_of_vertices()}")
                elif command == "3":
                    self.edge_exists_ui()
                elif command == "4":
                    self.get_in_degree_of_vertex_ui()
                elif command == "5":
                    self.get_out_degree_of_vertex_ui()
                elif command == "6":
                    self.get_the_outbound_edges_ui()
                elif command == "7":
                    self.get_the_inbound_edges_ui()
                elif command == "8":
                    self.get_cost_of_edge_ui()
                elif command == "9":
                    self.modify_the_cost_of_edge_ui()
                elif command == "10":
                    self.add_edge_ui()
                elif command == "11":
                    self.remove_edge_ui()
                elif command == "12":
                    self.add_vertex_ui()
                elif command == "13":
                    self.remove_vertex_ui()
                elif command == "14":
                    self.modified_file()
                    self.save_graph_to_file()
                elif command == "15":
                    self.sort_topological_and_show_extra_stuff_ui()
                elif command == "0":
                    done = True
                else:
                    print("Bad command!\n")
                print("Command ran successfully!")
            except Exception as e:
                print("Error: " + str(e))

    def sort_topological_and_show_extra_stuff_ui(self):
        sorted_list = self._graph.sort_topological()

        # printing the result of the topological ordering
        for x in sorted_list:
            print(x, " ", end="")
        print()

        time_list = self._graph.calculate_times(sorted_list)
        print("Total time of the project is: ", time_list['Y'][4])

        for x in time_list:
            print("Earliest starting time for activity ", x, " is ", time_list[x][0], " and the latest is ",
                  time_list[x][1])

        print("The critical points are: ", end="")
        for x in time_list:
            if time_list[x][4] == time_list[x][3]:
                print(x, end=" ")
        print()

    def read_table_from_file_ui(self):
        self._filename = input("Give file name: ")

        try:
            filepath = Path(self._filename)
            if filepath.is_file():
                with open(self._filename, "r") as file:
                    self._graph = Graph(0)

                    while True:
                        # reading the line and spliting it by space
                        line = file.readline()
                        line_list = line.replace('\n', ' ').split(' ')

                        if not line or line == "\n" or line == "":  # if it reached the end of the file
                            break

                        try:  # adding the activity name if it doesnt exist
                            self._graph.add_vertex(line_list[0])
                        except GraphException:
                            pass

                        self._graph.add_vertex_cost(line_list[0], int(line_list[1]))  # saving the cost of the activity
                        for i in range(2, len(line_list)):
                            if line_list[i] == '':
                                break
                            try:  # adding the activity name if ti doesnt exist
                                self._graph.add_vertex(line_list[i])
                            except GraphException:
                                pass

                            # adding the edge
                            self._graph.add_edge(line_list[i], line_list[0], int(line_list[1]))

                    # adding the fictive X and Y nodes
                    try:  # adding the activity name if ti doesnt exist
                        self._graph.add_vertex("X")
                    except GraphException:
                        pass

                    self._graph.add_vertex_cost('X', 0)

                    # adding the edges from X to the starting ones
                    for vertex in self._graph.parse_vertices():
                        if self._graph.get_in_degree(vertex) == 0 and vertex != "X":
                            self._graph.add_edge("X", vertex, 0)

                    try:  # adding the activity name if ti doesnt exist
                        self._graph.add_vertex("Y")
                    except GraphException:
                        pass
                    self._graph.add_vertex_cost('Y', 0)

                    # adding the edges from the end vertices to Y
                    for vertex in self._graph.parse_vertices():
                        if self._graph.get_out_degree(vertex) == 0 and vertex != "Y":
                            self._graph.add_edge(vertex, "Y", 0)

            else:
                raise UIException("File doesn't exist.")
        except FileNotFoundError:
            raise UIException("File was not found!")

    def remove_vertex_ui(self):
        try:
            x = input("X (source): ").strip()
        except ValueError:
            raise UIException("Bad input!")

        self._graph.remove_vertex(x)

    def add_vertex_ui(self):
        try:
            x = input("X (source): ").strip()
        except ValueError:
            raise UIException("Bad input!")

        self._graph.add_vertex(x)

    def remove_edge_ui(self):
        try:
            x = input("X (source): ").strip()
            y = input("Y (target): ").strip()
        except ValueError:
            raise UIException("Bad input!")

        self._graph.remove_edge(x, y)

    def add_edge_ui(self):
        try:
            x = input("X (source): ").strip()
            y = input("Y (target): ").strip()
            cost = int(input("Cost: ").strip())
        except ValueError:
            raise UIException("Bad input!")

        self._graph.add_edge(x, y, cost)

    def modify_the_cost_of_edge_ui(self):
        try:
            x = input("X (source): ").strip()
            y = input("Y (target): ").strip()
            new_cost = int(input("New cost: ").strip())
        except ValueError:
            raise UIException("Bad input!")

        self._graph.modify_cost_of_edge(x, y, new_cost)

    def get_cost_of_edge_ui(self):
        try:
            x = int(input("X (source): ").strip())
            y = int(input("Y (target): ").strip())
        except ValueError:
            raise UIException("Bad input!")

        print(f"Cost of edge ({x}, {y}): {self._graph.get_cost_of_edge(x, y)}")

    def get_the_inbound_edges_ui(self):
        try:
            x = int(input("X (source): ").strip())
        except ValueError:
            raise UIException("Bad input!")
        string = ""

        for y in self._graph.parse_inbound_edges(x):
            string += str(y) + " "
        if string == "":
            string = "none"
        print("Inbound edges for " + str(x) + ": " + string)

    def get_the_outbound_edges_ui(self):
        try:
            x = int(input("X (source): ").strip())
        except ValueError:
            raise UIException("Bad input!")
        string = ""

        for y in self._graph.parse_outbound_edges(x):
            string += str(y) + " "
        if string == "":
            string = "none"
        print("Outbound edges for " + str(x) + ": " + string)

    def get_in_degree_of_vertex_ui(self):
        try:
            x = int(input("X (source): ").strip())
        except ValueError:
            raise UIException("Bad input!")
        print("In degree of " + str(x) + " : " + str(self._graph.get_in_degree(x)))

    def get_out_degree_of_vertex_ui(self):
        try:
            x = int(input("X (source): ").strip())
        except ValueError:
            raise UIException("Bad input!")
        print("Out degree of " + str(x) + " : " + str(self._graph.get_out_degree(x)))

    def edge_exists_ui(self):
        try:
            x = int(input("X (source): ").strip())
            y = int(input("Y (target): ").strip())
        except ValueError:
            raise UIException("Bad input!")
        edge_exists = self._graph.edge_exists(x, y)
        if edge_exists is True:
            print("It exists!")
        else:
            print("It doesn't exist!")

    def modified_file(self):
        self._ex_filename = self._filename
        self._filename = self._filename[:-4] + "_modified.txt"

    def read_from_file(self):
        """
        Reads from a file in both ways
        :return: -
        raises UIException if something went wrong with the file
        """
        self._filename = input("Give file name: ")

        try:
            filepath = Path(self._filename)
            if filepath.is_file():
                with open(self._filename, "r") as file:
                    first_line = file.readline()
                    first_line_list = first_line.rstrip("\n").split(' ')
                    if len(first_line_list) == 2:
                        # case in which the first 2 numbers are the number of vertices and edges
                        self._graph = Graph(int(first_line_list[0]))

                        # reading edges
                        for i in range(0, int(first_line_list[1])):
                            line_list = file.readline().rstrip("\n").split(' ')
                            self._graph.add_edge(int(line_list[0]), int(line_list[1]), int(line_list[2]))
                    elif len(first_line_list) == 3:
                        # case in which it starts reading already the edges with everything
                        line_list = first_line_list
                        while True:
                            if len(line_list) == 1:
                                try:
                                    self._graph.add_vertex(int(line_list[0]))
                                except GraphException:
                                    pass
                            else:
                                # adding the vertices if they dont exist
                                try:
                                    self._graph.add_vertex(int(line_list[0]))
                                except GraphException:
                                    pass

                                try:
                                    self._graph.add_vertex(int(line_list[1]))
                                except GraphException:
                                    pass

                                # adding the edge
                                self._graph.add_edge(int(line_list[0]), int(line_list[1]), int(line_list[2]))

                            # reading next line
                            line = file.readline()
                            if not line or line == "\n" or line == "":  # if it reached the end of the file
                                break
                            line_list = line.split(' ')
            else:
                raise UIException("File doesn't exist.")
        except FileNotFoundError:
            raise UIException("File was not found!")

    def generate_graph(self, n, m):
        '''
        Generates a graph with n vertices and m edges
        :param n: The number of vertices
        :param m: The number of edges
        :return: -
        raises GraphException if the numbers are incorrect
        '''
        if n < 0 or m < 0:
            raise GraphException("Incorrect number of vertices/edges!")
        if m > n * n:
            raise GraphException("Incorrect number of edges!")
        self._graph = Graph(n)
        max_cost = m * 10
        while m != 0:
            for x in range(n):
                nr_of_edges_to_create = random.randint(0, n)
                for i in range(nr_of_edges_to_create):
                    y = random.randint(0, n - 1)
                    if not self._graph.edge_exists(x, y) and m > 0:
                        cost = random.randint(0, max_cost)
                        self._graph.add_edge(x, y, cost)
                        m = m - 1

    def save_graph_to_file(self):
        # self._filename = self._filename[:-4] + "_mofied.txt"
        try:
            with open(self._filename, "w") as file:
                for x in self._graph.parse_vertices():
                    vert_out = list(self._graph.parse_outbound_edges(x))
                    vert_in = list(self._graph.parse_inbound_edges(x))
                    if len(vert_out) == 0 and len(vert_in) == 0:
                        # means that it s an isolated vertex
                        line = str(x)
                        file.write(line + "\n")
                        continue

                    for vout in vert_out:
                        line = str(x) + " " + str(vout) + " " + str(self._graph.get_cost_of_edge(x, vout))
                        file.write(line + "\n")
                file.close()
                self._filename = self._ex_filename

        except FileNotFoundError:
            raise UIException("Something went wrong with the files")
