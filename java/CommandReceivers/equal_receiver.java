package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.LinesManager;
import Mode.Mode;

import java.util.List;

public class equal_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public equal_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        int lineIndex = getLineIndex();
        try {
            System.out.println(lineIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
            e.printStackTrace();
        }
    }

    @Override
    public void reverseAction() {

    }

    private int getLineIndex() {
        List<String> addressList = commandSQL.getAddressList();
        if (addressList.get(0).equals(""))
            return this.editorLineManager.getLines().size();
        else if (addressList.size() == 1) {
            String tmp = addressList.get(0);
            if (tmp.equals("$"))
                return editorLineManager.getLines().size();
            else if (tmp.equals("."))
                return this.currentLine;
            else
                return Integer.parseInt(tmp);
        } else {
            String offset = addressList.get(0);
            int base = Integer.parseInt(addressList.get(1));
            if (offset.equals("+"))
                return this.currentLine + base;
            else if (offset.equals("-"))
                return this.currentLine - base;
            else {
                StringBuilder stringBuilder = new StringBuilder();
                for (String anAddressList : addressList) stringBuilder.append(anAddressList);
                return Integer.parseInt(stringBuilder.toString());
            }
        }
    }


    private void Initialize(CommandSQL commandSQL) {
        if (this.commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            this.commandSQL.setEd(false);
        }
        this.commandSQL.setMode(Mode.Command);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
    }
}
