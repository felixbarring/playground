
import java.util.concurrent.Semaphore;


public class BarberProblem {

  class Barber implements Runnable{

    Semaphore requestHariCut = new Semaphore(0);
    Semaphore completedCut = new Semaphore(0);
    
    Barber(){
      new Thread(this).start();
    }

    public void run(){
      while (true){
        try {
          requestHariCut.acquire(1);
          System.out.println("Working");
          Thread.sleep(1000);
          completedCut.release();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
    }
    
  }
  
  class Client implements Runnable{
    
    Barber barber;
    Client(Barber barber){
      this.barber = barber;
    }
    
    public void run(){
      barber.requestHariCut.release();
      try {
        barber.completedCut.acquire(1);
        System.out.println("Client leaves");
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
  
  Barber barbers[] = {new Barber(), new Barber(), new Barber()};  
  
  BarberProblem(){ 
    for(int i = 0; i < 10; i++){
      new Thread(new Client(barbers[i%barbers.length])).start();
    }
  }
  
  public static void main(String[] args){
    new BarberProblem();
  }
  
  
}
