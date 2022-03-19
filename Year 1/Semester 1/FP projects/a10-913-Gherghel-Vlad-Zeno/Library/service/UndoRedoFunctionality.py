"""
Command design pattern -> telling the program to do something at a later time
"""


class UndoService:
    def __init__(self):
        # List of operations with support for undo/redo
        self._history = []
        self._index = -1

    def restart(self):
        self._history.clear()
        self._index = -1

    def record(self, operation):
        if self._index != len(self._history) - 1:
            length = len(self._history)
            for index in range(self._index+1, length):
                del self._history[index]
                length += 1
                index -= 1

        self._index += 1
        self._history.append(operation)

    def undo(self):
        if self._index == -1:
            return False

        self._history[self._index].undo()
        self._index -= 1
        return True

    def redo(self):
        if self._index == len(self._history) - 1:
            return False

        self._index += 1
        self._history[self._index].redo()
        return True


class CascadedOperation:
    def __init__(self, *operations):
        self._operations = operations

    def undo(self):
        for oper in self._operations:
            oper.undo()

    def redo(self):
        for oper in self._operations:
            oper.redo()


class Operation:
    def __init__(self, fun_call_undo, fun_call_redo):
        self._fun_call_undo = fun_call_undo
        self._fun_call_redo = fun_call_redo

    def undo(self):
        self._fun_call_undo()

    def redo(self):
        self._fun_call_redo()


class FunctionCall:
    def __init__(self, fun_ref, *fun_params):
        self._fun_ref = fun_ref
        self._fun_params = fun_params

    def call(self):
        return self._fun_ref(*self._fun_params)

    def __call__(self):
        return self.call()