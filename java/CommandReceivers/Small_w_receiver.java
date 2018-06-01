package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.io.File;
import java.util.List;

public class Small_w_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;
    private String targetFilePath;

    public Small_w_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        List<String> addressList = commandSQL.getAddressList();
        List<String> rearList = commandSQL.getRearList();
        int beginIndex;
        int endIndex;
        int[] tmpArr;
        if (addressList.get(0).equals("")) {
            tmpArr = new int[]{1, editorLineManager.getLines().size()};
        } else
            tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
        beginIndex = tmpArr[0];
        endIndex = tmpArr[1];

        try {
            String tmp = rearList.get(0);
            if (tmp.equals("") && this.targetFilePath == null)
                throw new NullPointerException();
            if (tmp.equals("")) {
                AddressAnalyser.listToFile(editorLineManager.getLines().subList(beginIndex - 1, endIndex), new File(this.targetFilePath));
            } else {
                AddressAnalyser.listToFile(editorLineManager.getLines().subList(beginIndex - 1, endIndex), new File(tmp));
            }
            commandSQL.setSaved(true);
        } catch (NullPointerException | IndexOutOfBoundsException e) {
            System.out.println("?");
            e.printStackTrace();
        }


    }

    @Override
    public void reverseAction() {

    }

    private void Initialize(CommandSQL commandSQL) {
        if (commandSQL.getMode() == Mode.Input) {
            System.out.println("Mode error!");
            commandSQL.setEd(false);
        }
        commandSQL.setMode(Mode.Input);
        this.editorLineManager = new LinesManager(commandSQL.getEditFile().getPath());
        this.currentLine = commandSQL.getCurrentLine();
        this.targetFilePath = commandSQL.getDefaultFileName();
    }
}
