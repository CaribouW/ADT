package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.ConsoleManager;
import Manager.LinesManager;
import Mode.Mode;
import edLineEditor.EDLineEditor;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

import static Manager.AddressAnalyser.listToFile;
import static Manager.AddressAnalyser.readFromConsole;

/**
 * (.)a		切换到输入模式，将新输入的文本追加到指定行的后面，当前行被设为输入文本的最后一行。
 * 所有初始化时都获取一次当前行，结束action时都保存一次当前行
 *
 * @author lfm
 * @time 5.23
 */
public class a_Receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;
    private LinesManager consoleLineManager;

    public a_Receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        readFromConsole(commandSQL);
        this.commandSQL.setMode(Mode.Command);
        this.consoleLineManager = new LinesManager(commandSQL.getConsoleFile().getPath());

        int lineIndex = getLineIndex(commandSQL, currentLine, editorLineManager);
        try {
            List<String> console = addToEditor(lineIndex);
            if (console.size() == 0)
                return;
            this.currentLine = lineIndex + console.size();
            commandSQL.setCurrentLine(currentLine);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }
    }

    //与d互为类似反操作
    @Override
    public void reverseAction() {
        String lastNode = commandSQL.getFileStack().peek();
        String[] strings = lastNode.split("##");
        int beginLine = Integer.parseInt(strings[1]) + 1;
        int undoSize = Integer.parseInt(strings[2]);
        int endLine = beginLine + undoSize - 1;
        EDLineEditor.consoleManager.launchCommand(beginLine + "," + endLine + "d");
        commandSQL.getFileStack().pop();
    }

    private List<String> addToEditor(int lineIndex) throws IndexOutOfBoundsException {
        List<String> console = consoleLineManager.getLines();
        List<String> editor = editorLineManager.getLines();
        if (commandSQL.getDefaultFileName() == null) {
            listToFile(console, commandSQL.getEditFile());
            return console;
        }

        int consoleSize = console.size();
        int editorSize = editor.size();
        List<String> result = new LinkedList<>();
        for (int i = 0; i < consoleSize + editorSize; i++) {
            if (i < lineIndex)
                result.add(editor.get(i));
            else if (i < lineIndex + consoleSize)
                result.add(console.get(i - lineIndex));
            else
                result.add(editor.get(i - consoleSize));
        }
        listToFile(result, commandSQL.getEditFile());

        //stack push
        if (!commandSQL.isUndo()) {
            Stack<String> stringStack = commandSQL.getFileStack();
            stringStack.push(commandSQL.getCommandLine() + "##" + currentLine + "##" + consoleSize);

        }
        return console;
    }


    private int getLineIndex(CommandSQL commandSQL, int currentLine, LinesManager editorLineManager
    ) {
        return AddressAnalyser.getLineIndex(commandSQL, currentLine, editorLineManager);
    }


    private void Initialize(CommandSQL commandSQL) {
        if (commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            commandSQL.setEd(false);
        }
        commandSQL.setSaved(false);
        commandSQL.setMode(Mode.Input);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
    }
}
