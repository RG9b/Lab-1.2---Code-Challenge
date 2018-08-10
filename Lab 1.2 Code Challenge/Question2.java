import javax.swing.JOptionPane;

public class Question2 {
	
	private void sort(int n,int a[]){
		int i,j,aux;
		for (j = 0; j < n-1; j++) {
		    int iMin = j;
		    for ( i = j+1; i < n; i++) {
		        if (a[i] < a[iMin]) {
		            iMin = i;
		        }
		    }
		    if(iMin != j) {
		        aux = a[j];
				a[j] = a[iMin];
				a[iMin]= aux;
		    }
		}
	}
	private int [] resize(int[] a) {
		int[] temp = new int [a.length+1];
		for (int i = 0; i < a.length; i++) {
			temp[i]=a[i];
		}
		return temp;
	}
	public static void main(String[] args) {
		Question2 ejemplo2 = new Question2();
		int seleccion=0;
		int posicion =0;
		int [] a = new int [0];
		while(seleccion!=2) {
			seleccion = JOptionPane.showOptionDialog(null,"Que quieres hacer", null,JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,null, new Object[] { "Mediana", "Agregar", "Terminar"},null);
			if(seleccion==1) {
				a = ejemplo2.resize(a);
				a[posicion]= Integer.parseInt(JOptionPane.showInputDialog("Numero a agregar:"));
				posicion++;
				ejemplo2.sort(a.length, a);
			}else if (seleccion==0){
				long startTime = System.nanoTime();
				if (a.length%2==0) {
					JOptionPane.showMessageDialog(null, "La mediana es: "+((a[(a.length/2)-1]+a[a.length/2])/2));
					//System.out.println("La mediana es: "+((a[(a.length/2)-1]+a[a.length/2])/2));
				}
				else{
					JOptionPane.showMessageDialog(null, "La mediana es: "+(a[(a.length/2)]));
					//System.out.println("La mediana es: "+(a[(a.length/2)]));
				}
				System.out.println((System.nanoTime()-startTime));
			}
		}
	}
}
