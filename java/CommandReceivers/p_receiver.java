package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.LinesManager;
import Mode.Mode;

import java.util.List;

import static Manager.AddressAnalyser.getLineIndex;
import static Manager.AddressAnalyser.getLineRange;

public class p_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public p_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        int beginIndex;
        int endIndex = -1;
        this.commandSQL.setMode(Mode.Command);
        List<String> addressList = commandSQL.getAddressList();
        if (addressList.size() == 1) {
            String tmp = addressList.get(0);
            if (tmp.equals("") || tmp.equals(".")) {
                beginIndex = endIndex = currentLine;
            } else if (tmp.equals(",")) {
                beginIndex = 1;
                endIndex = editorLineManager.getLines().size();

            } else if (tmp.equals(";")) {
                beginIndex = currentLine;
                endIndex = editorLineManager.getLines().size();

            } else if (tmp.equals("$")) {
                beginIndex = endIndex = editorLineManager.getLines().size();
            } else {
                beginIndex = endIndex = Integer.parseInt(tmp);
            }
            this.currentLine = endIndex;
        } else if (!addressList.contains(",")) {
            beginIndex = getLineIndex(commandSQL, currentLine, editorLineManager);
            this.currentLine = beginIndex;
        } else {
            int[] range = getLineRange(commandSQL, editorLineManager, currentLine);
            beginIndex = range[0];
            endIndex = range[1];
            this.currentLine = endIndex;
        }
        output(beginIndex, endIndex);
        commandSQL.setCurrentLine(currentLine);
    }

    @Override
    public void reverseAction() {

    }

    private void output(int beginIndex, int endIndex) {
        try {
            if (endIndex == -1) {
                System.out.println(editorLineManager.getLines().get(beginIndex - 1));
            } else {
                if (beginIndex > endIndex)
                    throw new IndexOutOfBoundsException();
                for (int begin = beginIndex - 1; begin < endIndex; begin++) {
                    String tmp = editorLineManager.getLines().get(begin);
                    System.out.println(tmp);
                }
            }
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
        }
    }

    private void Initialize(CommandSQL commandSQL) {
        if (commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            commandSQL.setEd(false);
        }
        commandSQL.setMode(Mode.Input);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
    }
}
