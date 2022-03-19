package Repository;

import Models.Exceptions.MyException;
import Models.States.PrgState;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Repo implements IRepo{
    private List<PrgState> prgStateList;
    private String logFilePath = "default.txt";


    public Repo(String logFilePath){

        this.prgStateList = new ArrayList<PrgState>();
        this.logFilePath = logFilePath;
    }

    public void addPrgState(PrgState state){
        this.prgStateList.add(state);
    }

    @Override
    public void logPrgStateExec(PrgState prgState) throws MyException {
        PrintWriter pw=null;
        try{
            pw=new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
            pw.println(prgState.toFileFormatString());
        }
        catch (IOException io) {
            System.err.println("Error at opening the file/writing "+io);
        }
        finally {
            if (pw!=null)
                pw.close();
        }

    }

    @Override
    public void clearLogFile() throws MyException {
        PrintWriter pw=null;
        try{
            pw=new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath)));
            pw.print("");
        }
        catch (IOException io) {
            System.err.println("Error at opening the file/writing "+io);
        }
        finally {
            if (pw!=null)
                pw.close();
        }
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.prgStateList;
    }

    @Override
    public void setPrgList(List<PrgState> newPrgList) {
        this.prgStateList = newPrgList;
    }


}
