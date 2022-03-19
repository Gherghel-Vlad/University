package Controller;

import Exceptions.RepoException;
import Repository.Repo;
import Model.Vehicle;

public class Controller {
    private Repo repo;

    public Controller(Repo repo){
        this.repo = repo;
    }

    public void add(Vehicle v) throws RepoException {
        repo.add(v);
    }

    public void remove(String name) throws RepoException{
        repo.remove(name);
    }

    public Vehicle[] filter(int price){
        return repo.filter(price);
    }

    public Repo getRepo(){
        return repo;
    }

    public int getLength(){
        return repo.getCurrentIndex();
    }

    public String toString(){
        return repo.toString();
    }
}
