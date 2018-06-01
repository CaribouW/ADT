package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.List;

/*
* (.+1)z[n]	从指定行，一次向后移动n行，打印包含指定行以及其后n行的内容。当前行被设为最后被打印的行。
	            当指定行到末尾行不足n行时，打印当前行到末尾行。
	            当参数n指定时，必为正整数；不指定时，打印当前行到末尾行。

* */
public class z_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;

    public z_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        int maxSize = editorLineManager.getLines().size();
        int[] tmp = getLineIndex();
        int begin = tmp[0];
        int appendSize = tmp[1];
        if (begin + appendSize > maxSize) {
            appendSize = maxSize - begin;
        }
        output(begin, appendSize);

        commandSQL.setCurrentLine(begin + appendSize);
    }

    @Override
    public void reverseAction() {

    }

    private void output(int begin, int appendSize) {
        List<String> outPut = editorLineManager.getLines().subList(begin - 1, begin + appendSize);
        for (String s : outPut)
            System.out.println(s);
    }

    private int[] getLineIndex() {
        int begin;
        int appendSize;
        List<String> addressList = commandSQL.getAddressList();
        List<String> rearList = commandSQL.getRearList();
        if (addressList.get(0).equals(""))
            begin = currentLine + 1;
        else
            begin = AddressAnalyser.getLineIndex(commandSQL, currentLine, editorLineManager);
        if (rearList.get(0).equals(""))
            appendSize = editorLineManager.getLines().size() - begin;
        else
            appendSize = Integer.parseInt(rearList.get(0));
        return new int[]{begin, appendSize};

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
