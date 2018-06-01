package Manager;


import java.io.*;

/**
 * Be used to connect with the input of the users and cope with the info
 * that the users have input into the bash.
 * <p>
 * The buff context will be stored in a new file.
 *
 * @author lfm
 * @time 5.22
 */
public class InputStartManager {
    private String defaultFilePath = "";
    private String buffFile = "Buff.txt";

    /**
     * @param inputLine :The first line that the user input.
     * @return :The buff file, which can be used to generate the IO stream and
     * finish other commands.
     */
    public File InputStart(String inputLine) {
        String[] tmpArr = inputLine.split(" ");

        if (tmpArr[0].equals("ed")) {
            /*
             *If "ed file"
             * */
            if (tmpArr.length == 2) {
                setDefaultFilePath(tmpArr[1]);
            }
            /*
             * If "ed"
             * */
            else
                setDefaultFilePath(null);
            /*
             * Get the Pointed file obj
             * */
            return getBuffFile();
        } else {
            //input error. then return null obj and we would print "?"
            return null;
        }
    }

    public String getDefaultFilePath() {
        return this.defaultFilePath;
    }

    /**
     * @return The buff file obj
     */
    private File getBuffFile() {
        try {
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.buffFile, false));
            if (this.defaultFilePath == null)
                return new File(this.buffFile);
            else {
                BufferedReader bufferedReader = new BufferedReader(new FileReader(this.defaultFilePath));
                String tmp;
                while ((tmp = bufferedReader.readLine()) != null) {
                    bufferedWriter.write(tmp + "\n");
                    bufferedWriter.flush();
                }
                bufferedReader.close();
                bufferedWriter.close();
            }
        } catch (IOException e) {
            System.out.println(e.getMessage() + "getBuffFile");
        }
        return new File(this.buffFile);
    }

    private void setDefaultFilePath(String defaultFilePath) {
        this.defaultFilePath = defaultFilePath;
    }

}
