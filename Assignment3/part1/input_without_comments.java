 
 
 
 
 
 
public class DemoClass
{
    private int x;

    public DemoClass()
    {
         
        x = 0;
    }

    public DemoClass(int x)
    {
         
         
         
        this.x = x;
    }

    public DemoClass(DemoClass otherDemo)
    {
         
        this.x = otherDemo.x;
    }

     
    public static void s1() {
        return;
    }
     
    public void i1() {
        return;
    }

     
     
    public static void s2() {
 
        s1();        
        return;
    }

     
     
    public void i2() {
        s1();        
        i1();        
        return;
    }

     
     
    public void overloadTester() {
        System.out.println("");

        overload((byte)1);
        overload((short)1);
        overload(1);
        overload(1L);
        overload(1.0f);
        overload(1.0);
        overload('');
        overload(true);
    }
    
    public void overload(byte b) {
        System.out.println("");
    }    
    public void overload(short s) {
        System.out.println("");
    }    
    public void overload(int i) {
        System.out.println("");
    }
    public void overload(long l) {
        System.out.println("");
    }
    public void overload(float f) {
        System.out.println("");
    }
    public void overload(double d) {
        System.out.println("");
    }    
    public void overload(char c) {
        System.out.println("");
    }    
    public void overload(boolean b) {
        System.out.println("");
    }    

    public static void main(String[] args) {
        DemoClass dc = new DemoClass();
        dc.overloadTester();
    }
}

 
