
import java.util.concurrent.locks.*;

public class SemaphoreBarrier {
  
  private final Lock lock = new ReentrantLock();
  private final Condition cond = lock.newCondition();
  private int counter;
  private int release;
  
  SemaphoreBarrier(int workers){
    release = workers;
  }
  
  public void join(){
    lock.lock();
    try{
      if(++counter == release) cond.signalAll();
    } finally{
      lock.unlock();
    }
  }
  
}
