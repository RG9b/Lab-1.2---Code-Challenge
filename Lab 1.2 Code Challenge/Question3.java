
import javax.swing.JOptionPane;

public class Question3 {
	
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
	private int [] prohibida(int n,int k) {
		int temp[]=new int [k];
		int y;
		int z=0;
		int cont =0;
		while(cont!=k){
			y = (int)(Math.random() * n);
			if (comparar(temp, y)) temp[cont++]=y;
			if (z==0 && y==0) {
				temp[cont++]=y;
				z++;
			}
		}
		return temp;
	}
	private boolean comparar(int arreglo[],int x) {
		int temp = 0;
		for (int i = 0; i < arreglo.length; i++){
		    if (arreglo[i]==x) temp++;
		}
		if (temp==0) return true;
		
		return false;
	}
	private int lista(int n,int [] k) {
		float probabilidad;
		int size = n-k.length;
		int []temp=new int [size];
		int contador1=0;
		int contador2=0;
		int devolver;
		System.out.print("\nLa lista de numeros admitidos es: ");
		
		for (int i = 0; i <n; i++) {
			if(contador1==k.length||i!=k[contador1]) {
				temp[contador2++]=i;
				System.out.print(temp[(contador2)-1]+" ");
			}else {
				contador1++;
			}
		}
		probabilidad= 1/(float)size*100;
		devolver = temp[(int) (Math.random() * size)];
		System.out.println("\nLa probabilidad de cada numero que no esta en la lista es: "+ (int)probabilidad+" %");
		return devolver;
	}
	public static void main(String[] args) {
		
		Question3 ejemplo3 = new Question3();
		int n = Integer.parseInt(JOptionPane.showInputDialog("Numero de elementos: "));
		int k = Integer.parseInt(JOptionPane.showInputDialog("Numero de elementos prohibidos: "));
		
		if (n==k) JOptionPane.showMessageDialog(null, "K y N no pueden ser iguales");
		else {
			long startTime = System.nanoTime();
			int prohibida [] = ejemplo3.prohibida(n, k);
			ejemplo3.sort(k, prohibida);
			System.out.print("La lista prohibida es: ");
			for (int i = 0; i < prohibida.length; i++) {
				System.out.print(prohibida[i]+" ");
			}
			System.out.println("El numero aleatorio es: " + ejemplo3.lista(n, prohibida));
			System.out.println((System.nanoTime()-startTime));
		}
	}
}
