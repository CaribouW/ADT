package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.*;

public class c_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;
    private LinesManager consoleLineManager;

    public c_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        readFromConsole(commandSQL);
        this.commandSQL.setMode(Mode.Command);
        this.consoleLineManager = new LinesManager(commandSQL.getConsoleFile().getPath());
        int beginIndex;
        int endIndex;
        int[] tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
        beginIndex = tmpArr[0];
        endIndex = tmpArr[1];
        try {
            List<String> console = changeToEditor(beginIndex, endIndex);
            if (console.size() == 0)
                return;
            int removeSize;
            if (endIndex == -1)
                removeSize = 1;
            else {
                removeSize = endIndex - +1;
            }
            this.currentLine = currentLine + console.size() - removeSize;
            commandSQL.setCurrentLine(currentLine);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
            e.printStackTrace();
        }
    }

    @Override
    public void reverseAction() {

    }

    private List<String> changeToEditor(int beginIndex, int endIndex)
            throws IndexOutOfBoundsException {
        if (endIndex == -1) {
            return singleChange(beginIndex);
        } else {
            if (endIndex < beginIndex)
                throw new IndexOutOfBoundsException();
            else {
                return rangeChange(beginIndex, endIndex);
            }
        }
    }


    private int getLineIndex(CommandSQL commandSQL, int currentLine, LinesManager editorLineManager
    ) {
        return AddressAnalyser.getLineIndex(commandSQL, currentLine, editorLineManager);
    }

    private List<String> rangeChange(int beginIndex, int endIndex) {
        List<String> console = consoleLineManager.getLines();
        List<String> editor = editorLineManager.getLines();
        int consoleSize = console.size();
        int editorSize = editor.size();
        List<String> result = new LinkedList<>();
        int removeSize = endIndex - beginIndex + 1;
        for (int i = 0; i < consoleSize + editorSize - removeSize; i++) {
            if (i < beginIndex - 1)
                result.add(editor.get(i));
            else if (i < beginIndex + consoleSize - 1)
                result.add(console.get(i - beginIndex + 1));
            else
                result.add(editor.get(i - consoleSize + removeSize));
        }

        listToFile(result, commandSQL.getEditFile());
        return console;
    }

    private List<String> singleChange(int beginIndex) {
        return rangeChange(beginIndex, beginIndex);
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
