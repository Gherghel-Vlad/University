package Controller;

import Models.ADTs.MyIHeap;
import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Statements.IStmt;
import Models.States.PrgState;
import Models.Values.IValue;
import Models.Values.RefValue;
import Repository.IRepo;

import java.util.*;
import java.util.stream.Collectors;

public class Controller {
    IRepo repo;
    boolean displayFlag;

    public Controller(IRepo r){
        this.repo = r;
    }

    public Controller(IRepo r, boolean df){
        this.repo = r;
        this.displayFlag = df;
    }

    public void setDisplayFlag(boolean df){
        this.displayFlag = df;
    }

    public PrgState oneStepExecution(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        if(stk.empty())
            throw new MyException("Prgstate stack is empty.");

        IStmt crtStmt = stk.pop();
        PrgState st =  crtStmt.execute(state);

        if(this.displayFlag){
            System.out.println(st.toString());
        }

        return st;
    }

    public void allStep() throws MyException{

        this.repo.clearLogFile();

        PrgState prg = this.repo.getCrtPrg();
        if(this.displayFlag){
            System.out.println(prg.toString());
        }
        this.repo.logPrgStateExec();
        while(!prg.getStk().empty()){
            oneStepExecution(prg);
            this.repo.logPrgStateExec();

            /*
            prg.getHeap().setContent(safeGarbageCollector(
                    getAddrFromSymTable(prg.getSymTable().getContent().values()),
                    getReferenceAddrFromHeap(prg.getHeap().getContent(), getAddrFromSymTable(prg.getSymTable().getContent().values())),
                    prg.getHeap().getContent()));

            */

            prg.getHeap().setContent(safeGarbageCollector(
                    getAddrFromSymTable(prg.getSymTable().getContent().values()),
                    getReferenceAddrFromHeap(prg.getHeap().getContent()),
                    prg.getHeap().getContent()));

            if(this.displayFlag){
                System.out.println(prg.toString());
            }

            this.repo.logPrgStateExec();
        }
    }

    Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapRefAddrList, Map<Integer, IValue> heap){
        return heap.entrySet().stream().filter(e-> (symTableAddr.contains(e.getKey()) || heapRefAddrList.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    List<Integer> getAddrFromSymTable(Collection<IValue> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
               .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }


    List<Integer> getReferenceAddrFromHeap(Map<Integer, IValue> heap){
        return heap.values().stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }


    /*
    List<Integer> getReferenceAddrFromHeap(Map<Integer, IValue> heap, List<Integer> symTableValues){
        List<Integer> res = new ArrayList<>();

        symTableValues.forEach(v-> {
            Integer v1 =v;
            while(heap.containsKey(v1) && heap.get(v1) instanceof RefValue){
                res.add(v1);
                v1 = ((RefValue) heap.get(v1)).getAddress();
            }
            res.add(v1);
        });

        return res;
    }
    */
}























