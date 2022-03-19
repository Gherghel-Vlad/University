package Repository;

import Models.Exceptions.MyException;
import Models.States.PrgState;

import java.io.*;
import java.util.ArrayList;

public class Repo implements IRepo{
    private ArrayList<PrgState> prgStateList;
    private String logFilePath = "default.txt";

    // might delete later
    public Repo(){

        this.prgStateList = new ArrayList<PrgState>();
    }

    public Repo(String logFilePath){

        this.prgStateList = new ArrayList<PrgState>();
        this.logFilePath = logFilePath;
    }

    public void addPrgState(PrgState state){
        this.prgStateList.add(state);
    }

    @Override
    public void logPrgStateExec() throws MyException {
        PrintWriter pw=null;
        try{
            pw=new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
            pw.println(this.getCrtPrg().toFileFormatString());
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
    public PrgState getCrtPrg() {

        return this.prgStateList.get(0);
    }

}
