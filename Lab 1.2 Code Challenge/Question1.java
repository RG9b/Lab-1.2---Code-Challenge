import javax.swing.JOptionPane;

public class Question1 {
	
	public Object letra (String palabra) {
		char arreglo[] = new char[palabra.length()];
		String cadena = palabra;
		for (int i = 0; i < palabra.length(); i++){
		    arreglo[i] = cadena.charAt(i);
		}
		for (int i = 0; i < palabra.length(); i++){
		    if (comparar(arreglo, arreglo[i]))  return arreglo[i];
		}
		return null;
	}
	private boolean comparar(char arreglo[],char x) {
		int temp = 0;
		for (int i = 0; i < arreglo.length; i++){
		    if (arreglo[i]==x) temp++;
		}
		if (temp==1) return true;
		
		return false;
	}
	public static void main(String[] args) {
		Question1 prueba= new Question1();
		String palabra = JOptionPane.showInputDialog("Palabra a comparar:");
		long startTime = System.nanoTime();
		if (prueba.letra(palabra)== null) {
			JOptionPane.showMessageDialog(null, "Todos los caracteres se repiten");
			//System.out.println("Todos los caracteres se repiten");
		}else {
			JOptionPane.showMessageDialog(null, "El caracter que no se repite es: '"+prueba.letra(palabra)+"'");
			//System.out.println("El caracter que no se repite es: '"+prueba.letra(palabra)+"'");
		}
		System.out.println((System.nanoTime()-startTime));
	}
}
