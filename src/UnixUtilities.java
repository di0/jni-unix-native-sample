public class UnixUtilities {
	static {
		System.loadLibrary("unixenvironment");
	}

	private native String ipconfig();

	public static void main(String[] args) {
		UnixUtilities unixUtilities = new UnixUtilities();
		System.out.println("Native IP " + unixUtilities.ipconfig());
	}
}
