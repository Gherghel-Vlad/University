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
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {
    IRepo repo;
    boolean displayFlag;
    private ExecutorService executor;

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


    public void oneStepForAllPrg(List<PrgState> prgList) {
        prgList.forEach(prg-> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException e) {
                e.printStackTrace();
            }
        });

        List<Callable<PrgState>> callList = prgList.stream().map((PrgState p) -> (Callable<PrgState>)(() -> {return p.oneStepExecution();}))
                .collect(Collectors.toList());
        try {

            List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (InterruptedException | ExecutionException e) {
                            System.out.println(e.toString());
                        }
                        return null;
                    }).filter(p->p!=null)
                    .collect(Collectors.toList());

                    prgList.addAll(newPrgList);

        }
        catch (InterruptedException e){
            System.out.println(e.toString());
        }

        prgList.forEach(prg-> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException e) {
                e.printStackTrace();
            }
        });

        repo.setPrgList(prgList);
    }



    public void allStep() throws MyException{
        this.repo.clearLogFile();

        this.executor = Executors.newFixedThreadPool(2);

        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        while(prgList.size() > 0){
            prgList.get(0).getHeap().setContent(safeGarbageCollector(
                    getAddrFromSymTable(prgList),
                    getReferenceAddrFromHeap(prgList.get(0).getHeap().getContent(), getAddrFromSymTable(prgList)),
                    prgList.get(0).getHeap().getContent()));

            oneStepForAllPrg(prgList);

            prgList = removeCompletedPrg(repo.getPrgList());
        }

        executor.shutdownNow();

        repo.setPrgList(prgList);

    }

    public void oneStepForAll() throws MyException{
        try {
            this.repo.clearLogFile();

            this.executor = Executors.newFixedThreadPool(2);

            List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

            prgList.get(0).getHeap().setContent(safeGarbageCollector(
                    getAddrFromSymTable(prgList),
                    getReferenceAddrFromHeap(prgList.get(0).getHeap().getContent(), getAddrFromSymTable(prgList)),
                    prgList.get(0).getHeap().getContent()));

            oneStepForAllPrg(prgList);

            prgList = removeCompletedPrg(repo.getPrgList());


            executor.shutdownNow();

            repo.setPrgList(prgList);
        }
        catch (Exception e){
            throw new MyException("Program is done!");
        }
    }

    Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapRefAddrList, Map<Integer, IValue> heap){
        return heap.entrySet().stream().filter(e-> (symTableAddr.contains(e.getKey()) || heapRefAddrList.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    List<Integer> getAddrFromSymTable(List<PrgState> prgList){
        List<Integer> allSymTablesReferences = new ArrayList<Integer>();

        prgList.forEach((PrgState p) -> { allSymTablesReferences.addAll(p.getSymTable().getContent().values()
                .stream().filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList()));});

        return allSymTablesReferences;
    }


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

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList){
        return inPrgList.stream().filter(p->p.isNotCompleted()).collect(Collectors.toList());
    }
}























