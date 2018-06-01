package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.listToFile;

public class j_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public j_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        List<String> addressList = commandSQL.getAddressList();
        this.commandSQL.setMode(Mode.Command);
        int beginIndex;
        int endIndex;
        if (addressList.get(0).equals("")) {
            beginIndex = currentLine;
            endIndex = currentLine + 1;
        } else {
            int[] tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
            beginIndex = tmpArr[0];
            endIndex = tmpArr[1];
        }
        try {
            mergeIntoOneLine(beginIndex, endIndex);
            commandSQL.setCurrentLine(beginIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }

    }

    private void mergeIntoOneLine(int beginIndex, int endIndex) {
        List<String> targetNodes = editorLineManager.getLines();
        List<String> result = new LinkedList<>();

        List<String> mergeList = targetNodes.subList(beginIndex - 1, endIndex);
        StringBuilder stringBuilder = new StringBuilder();
        for (String s : mergeList)
            stringBuilder.append(s);
        for (int i = 1; i <= targetNodes.size(); i++) {
            String tmp = targetNodes.get(i - 1);
            if (i < beginIndex || i > endIndex)
                result.add(tmp);
            else if (i == beginIndex)
                result.add(stringBuilder.toString());
        }

        listToFile(result, commandSQL.getEditFile());
    }

    @Override
    public void reverseAction() {

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
