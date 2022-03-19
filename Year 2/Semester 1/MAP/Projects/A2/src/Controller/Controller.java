package Controller;

import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Statements.IStmt;
import Models.States.PrgState;
import Repository.IRepo;

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
        PrgState prg = this.repo.getCrtPrg();
        if(this.displayFlag){
            System.out.println(prg.toString());
        }
        while(!prg.getStk().empty()){
            oneStepExecution(prg);
            if(this.displayFlag){
                System.out.println(prg.toString());
            }
        }
    }


}
