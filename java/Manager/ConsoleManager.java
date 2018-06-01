package Manager;

import CommandControllers.CommandClient;
import CommandControllers.CommandSQL;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

/**
 * The entry of the programme
 *
 * @author lfm
 * @time 5.22
 */
public class ConsoleManager {
    private String defaultFileName;
    private File editFile;
    private boolean IsEd = false;    //ed 是否进入ed状态标志
    public static BufferedReader bufferedReader;
    private int currentLine = 0;
    private boolean IsInitial = false;
    private boolean IsSaved = true;
    public static Stack<String> commandStack = new Stack<>();
    public static boolean IsUndo = false;

    /**
     * Deal with the ed command.
     * We get file info from the ed command.
     */
    public void startLineOperation() {
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        try {
            InputStartManager inputStartManager = new InputStartManager();
            String startLine = bufferedReader.readLine();
            editFile = inputStartManager.InputStart(startLine);
            defaultFileName = inputStartManager.getDefaultFilePath();
            LinesManager editorLineManager = new LinesManager(editFile.getPath());
            currentLine = editorLineManager.getCurrentLine();
            if (editFile == null) {
                IsEd = false;
            } else {
                IsEd = true;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Cope with the commands
     */
    public void consoleReadOn() {
        String nextConsoleLine;
        while (this.IsEd && (nextConsoleLine = getNextConsoleLine()) != null) {
            launchCommand(nextConsoleLine);
        }
    }

    public void launchCommand(String nextConsoleLine) {
        CommandSQL commandSQL = getCommandSQL(nextConsoleLine);
        new CommandClient(commandSQL).doCommand();
        flushInfo(commandSQL);
    }

    private CommandSQL getCommandSQL(String nextConsoleLine) {
        CommandSQL commandSQL = new CommandSQL(nextConsoleLine, defaultFileName,
                editFile);
        commandSQL.setFileStack(commandStack);
        commandSQL.setUndo(IsUndo);
        commandSQL.setCurrentLine(this.currentLine);
        commandSQL.setEd(this.IsEd);//同步相关信息
        commandSQL.setSaved(this.IsSaved);
        commandSQL.setUndo(false);
        return commandSQL;
    }

    private void flushInfo(CommandSQL commandSQL) {
        commandStack = commandSQL.getFileStack();
        IsUndo = commandSQL.isUndo();
        this.IsEd = commandSQL.isEd();
        this.editFile = commandSQL.getEditFile();
        this.defaultFileName = commandSQL.getDefaultFileName();
        this.currentLine = commandSQL.getCurrentLine();
        this.IsSaved = commandSQL.isSaved();

    }

    /**
     * @return The next line in the console
     */

    private String getNextConsoleLine() {
//        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        /*
        疑惑：加了这句话之后OJ会判定readline的返回值为null 但本地没有问题
        之后网管说这不是系统的锅
        但用例应该写得用心一些，如果一次性把输入放入缓冲区，是不符合正常用户输入的
        */
        try {
            return bufferedReader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean isEd() {
        return IsEd;
    }

    public File getEditFile() {
        return this.editFile;
    }

    public boolean isInitial() {
        return IsInitial;
    }

    public void setInitial(boolean initial) {
        IsInitial = initial;
    }
}
