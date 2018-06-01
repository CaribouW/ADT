package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.listToFile;

public class t_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public t_receiver(CommandSQL commandSQL) {
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
            copyNodes(beginIndex, endIndex, singleIndex);
            commandSQL.setCurrentLine(singleIndex + (endIndex - beginIndex) + 1);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }

    }

    @Override
    public void reverseAction() {

    }

    private void copyNodes(int beginIndex, int endIndex, int singleIndex) {
        List<String> targetNodes = editorLineManager.getLines();
        List<String> result = new LinkedList<>();
        for (int i = 1; i <= targetNodes.size(); i++) {
            String tmp = targetNodes.get(i - 1);
            if (i != singleIndex)
                result.add(tmp);
            else {
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
