package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.listToFile;

public class d_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public d_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        this.commandSQL.setMode(Mode.Command);
        int beginIndex;
        int endIndex;
        int[] tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
        beginIndex = tmpArr[0];
        endIndex = tmpArr[1];
        try {
            deleteNodes(beginIndex, endIndex);
            if (endIndex < editorLineManager.getLines().size()) {
                currentLine = beginIndex;
            } else {
                currentLine = beginIndex - 1;
            }
            commandSQL.setCurrentLine(currentLine);

        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }

    }

    @Override
    public void reverseAction() {

    }

    private void deleteNodes(int beginIndex, int endIndex) throws IndexOutOfBoundsException {
        List<String> editor = editorLineManager.getLines();
        int editorSize = editor.size();
        List<String> result = new LinkedList<>();
        for (int line = 1; line <= editorSize; line++) {
            if (line < beginIndex || line > endIndex)
                result.add(editor.get(line - 1));
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
