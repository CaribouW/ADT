package Manager;

import CommandControllers.CommandSQL;

import java.io.*;
import java.util.List;

public class AddressAnalyser {
    public static void readFromConsole(CommandSQL commandSQL) {
        File consoleFile = commandSQL.getConsoleFile();
        try {
            BufferedReader bufferedReader = ConsoleManager.bufferedReader;
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(consoleFile));
            String tmpConsole;
            while ((tmpConsole = bufferedReader.readLine()) != null) {
                if (tmpConsole.equals(".")) {
                    break;
                }
                bufferedWriter.write(tmpConsole + "\n");
                bufferedWriter.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /*
     *(.)
     */
    public static int getLineIndex(int currentLine, LinesManager editorLineManager, List<String>
            addressList) {
        /*
         * 简单单行地址
         * */
        if (addressList.size() == 1) {
            String tmp = addressList.get(0);
            if (tmp.equals(".") || tmp.equals(""))
                return currentLine;
            else if (tmp.equals("$"))
                return editorLineManager.getLines().size();
            else
                return Integer.parseInt(tmp);
        } else if (addressList.contains("/") || addressList.contains("?")) {
            if (addressList.contains("/"))
                return findForward(currentLine, editorLineManager, addressList, true);
            else
                return findForward(currentLine, editorLineManager, addressList, false);
        } else {
            String offset = addressList.get(0);
            int base = Integer.parseInt(addressList.get(1));
            if (offset.equals("+"))
                return currentLine + base;
            else if (offset.equals("-"))
                return currentLine - base;
            else {
                StringBuilder stringBuilder = new StringBuilder();
                for (String anAddressList : addressList) stringBuilder.append(anAddressList);
                return Integer.parseInt(stringBuilder.toString());
            }
        }
    }

    private static int findForward(int currentLine, LinesManager editorLineManager, List<String> addressList, boolean b) {
        StringBuilder stringBuilder = new StringBuilder();
        int result = 0;
        for (String s : addressList) {
            if (s.equals("/") || s.equals("?"))
                continue;
            stringBuilder.append(s);
        }
        List<String> lines = editorLineManager.getLines();
        if (b) {

            if (currentLine == lines.size()) currentLine = 1;
            for (int line = currentLine + 1; line <= lines.size(); ) {
                String target = lines.get(line - 1);
                if (target.contains(stringBuilder.toString()))
                    return line;
                line++;
                if (line > lines.size())
                    line = 1;
                if (line == currentLine)
                    break;
            }
        } else {
            if (currentLine == 1) currentLine = lines.size();
            for (int line = currentLine - 1; line >= 0; ) {
                String target = lines.get(line - 1);
                if (target.contains(stringBuilder.toString()))
                    return line;
                line--;
                if (line < 0)
                    line = lines.size();
                if (line == currentLine)
                    return -1;
            }
        }
        return -1;
    }

    public static int getLineIndex(CommandSQL commandSQL, int currentLine, LinesManager editorLineManager
    ) {
        return getLineIndex(currentLine, editorLineManager, commandSQL.getAddressList());
    }

    /*
     *(.,.)
     */
    public static int[] getLineRange(CommandSQL commandSQL, LinesManager editorLineManager,
                                     int currentLine) {
        List<String> addressList = commandSQL.getAddressList();
        int size = addressList.size();
        int MaxLine = editorLineManager.getLines().size();
        int leftIndex = 0;
        int rightIndex = 0;
        /*
         *  "" "$" "," "." ";"(不包括复杂单行地址)
         * */
        if (size == 1) {
            String tmp = addressList.get(0);
            if (tmp.equals("") || tmp.equals(".")) {
                leftIndex = rightIndex = currentLine;
            } else if (tmp.equals("$")) {
                leftIndex = rightIndex = MaxLine;
            } else if (tmp.equals(",")) {
                leftIndex = 1;
                rightIndex = MaxLine;
            } else if (tmp.equals(";")) {
                leftIndex = currentLine;
                rightIndex = MaxLine;
            } else {
                leftIndex = rightIndex = getLineIndex(currentLine, editorLineManager, addressList);
            }
        }
        /*
         * (m,n)
         * */
        else if (addressList.contains(",")) {
            int dotIndex = addressList.indexOf(",");
            leftIndex = AddressAnalyser.getLineIndex(currentLine, editorLineManager, addressList.subList(0, dotIndex));
            rightIndex = AddressAnalyser.getLineIndex(currentLine, editorLineManager, addressList.subList(dotIndex + 1, size));
        }
        /*
         * 解析复杂单行地址
         * */
        else {
            leftIndex = rightIndex = getLineIndex(currentLine, editorLineManager, addressList);
        }
        return new int[]{leftIndex, rightIndex};
    }

    public static void listToFile(List<String> result, File file, boolean append) {
        try {
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(file, append));
            for (int i = 0; i < result.size(); i++) {
                String tmp = result.get(i);
                bufferedWriter.write(tmp + "\n");
                bufferedWriter.flush();
            }
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void listToFile(List<String> result, File file) {
        listToFile(result, file, false);
    }
}
