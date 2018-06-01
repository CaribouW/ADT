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

public class m_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public m_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        this.commandSQL.setMode(Mode.Command);
        int beginIndex;
        int endIndex;
        int singleIndex;
        int[] tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
        beginIndex = tmpArr[0];
        endIndex = tmpArr[1];
        singleIndex = AddressAnalyser.getLineIndex(currentLine, editorLineManager, commandSQL.getRearList());
        try {
            mergeNodes(beginIndex, endIndex, singleIndex);
            /*
             * 如果single在中间会怎么样？
             * 题目里也没说
             * */
            if (endIndex < singleIndex) {
                commandSQL.setCurrentLine(singleIndex);
            } else if (singleIndex < beginIndex) {
                commandSQL.setCurrentLine(singleIndex + (endIndex - beginIndex));
            }
            if (!commandSQL.isUndo()) {
                //stack push
                Stack<String> stringStack = commandSQL.getFileStack();
                stringStack.push(commandSQL.getCommandLine() + "##" + singleIndex + "##" + currentLine + "##" + beginIndex);
            }

        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }
    }

    //与自身互为反操作，需要三个数据
    @Override
    public void reverseAction() {
        String lastNode = commandSQL.getFileStack().pop();
        String[] strings = lastNode.split("##");
        int beginLine = Integer.parseInt(strings[1]) + 1;
        int endLine = Integer.parseInt(strings[2]);
        int singleLine = Integer.parseInt(strings[3]) - 1;
        EDLineEditor.consoleManager.launchCommand(3 + "m" + 4);
        commandSQL.getFileStack().pop();
    }

    private void mergeNodes(int beginIndex, int endIndex, int singleIndex) {
        List<String> targetNodes = editorLineManager.getLines();
        List<String> result = new LinkedList<>();
        for (int i = 1; i <= targetNodes.size(); i++) {
            String tmp = targetNodes.get(i - 1);
            if ((i < beginIndex || i > endIndex) && i != singleIndex)
                result.add(tmp);
            else if (i == singleIndex) {
                result.add(tmp);
                List<String> insert = targetNodes.subList(beginIndex - 1, endIndex);
                result.addAll(insert);
            }
        }

        listToFile(result, commandSQL.getEditFile());
    }

    private void Initialize(CommandSQL commandSQL) {
        if (commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            commandSQL.setEd(false);
        }
        commandSQL.setSaved(false);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
    }
}
