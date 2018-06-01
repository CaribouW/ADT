package CommandControllers;

import Mode.Mode;
import Splitter.AddressSplitter;
import Splitter.CommandSplitter;
import Splitter.RearParamSplitter;

import java.io.File;
import java.util.List;
import java.util.Stack;

/*
 * We use the three splitter to split the commandLine into three part
 * and we use switch to do something more
 *
 * @author lfm
 * @time 5.22
 * <p>
 * 更新
 * client.
 * Decide to wrap all of the resource info(file,commandLine) into this class
 * --5.23
 *
 * 更新
 * 完成注释内容
 * --6.1
 */

/**
 * The data base of the programme. we deliver this class to the commandReceiver.
 */
public class CommandSQL {
    private AddressSplitter addressSplitter;
    private RearParamSplitter rearParamSplitter;
    private CommandSplitter commandSplitter;
    private String commandLine; //控制台得到的命令行
    private List<String> addressList; //地址信息列表
    private List<String> rearList;    //尾参数信息列表
    private char middleParam;         //命令类型字符
    private boolean IsEd = false;    //ed 是否进入ed状态标志
    private boolean IsSaved = false; //编辑器缓冲区是否保存标志
    private Mode mode = Mode.Command;//ed模式

    /*
     * 关联的文件个数为三个
     * */

    /*
     * currentLine From[1] to lineSize
     * */
    private int currentLine = -1;    //当前行[1-max]
    private String defaultFileName;  //目标文件(最终)名称
    private File editFile;           //编辑器缓冲区文件
    private File consoleFile = new File("consoleFile.txt");  //input模式的输入缓冲区文件

    /*
     * Undo stack
     * */
    private Stack<String> fileStack;
    private boolean isUndo = false;

    /**
     * @param commandLine     :The whole command sentence
     * @param defaultFileName :Target file path
     * @param editFile
     */
    public CommandSQL(String commandLine, String defaultFileName, File editFile) {
        /*
         * Split the command line first.
         * Initialize the command info.
         * */
        this.commandLine = commandLine;
        this.commandSplitter = new CommandSplitter(commandLine);
        this.commandSplitter.doSplitCommand();
        this.addressSplitter = new AddressSplitter(commandSplitter);
        this.rearParamSplitter = new RearParamSplitter(commandSplitter);
        this.addressSplitter.doAddressSplit();
        this.rearParamSplitter.doRearSplit();
        this.addressList = addressSplitter.getAddressList();
        this.rearList = rearParamSplitter.getRearParamList();
        this.middleParam = commandSplitter.getMiddleCommand().charAt(0);
        /*
         * Initialize the file info
         * */
        this.defaultFileName = defaultFileName;
        this.editFile = editFile;
    }

    public List<String> getAddressList() {
        return addressList;
    }

    public List<String> getRearList() {
        return rearList;
    }

    public char getMiddleParam() {
        return middleParam;
    }

    public boolean isEd() {
        return IsEd;
    }

    public void setEd(boolean ed) {
        IsEd = ed;
    }

    public boolean isSaved() {
        return IsSaved;
    }

    public void setSaved(boolean saved) {
        IsSaved = saved;
    }

    public String getDefaultFileName() {
        return defaultFileName;
    }

    public void setDefaultFileName(String defaultFileName) {
        this.defaultFileName = defaultFileName;
    }

    public File getEditFile() {
        return editFile;
    }

    public void setEditFile(File editFile) {
        this.editFile = editFile;
    }

    public Mode getMode() {
        return mode;
    }

    public void setMode(Mode mode) {
        this.mode = mode;
    }

    public File getConsoleFile() {
        return consoleFile;
    }

    public void setConsoleFile(File consoleFile) {
        this.consoleFile = consoleFile;
    }

    public int getCurrentLine() {
        return currentLine;
    }

    public void setCurrentLine(int currentLine) {
        this.currentLine = currentLine;
    }

    public Stack<String> getFileStack() {
        return fileStack;
    }

    public void setFileStack(Stack<String> fileStack) {
        this.fileStack = fileStack;
    }

    public String getCommandLine() {
        return commandLine;
    }

    public boolean isUndo() {
        return isUndo;
    }

    public void setUndo(boolean undo) {
        isUndo = undo;
    }
}
