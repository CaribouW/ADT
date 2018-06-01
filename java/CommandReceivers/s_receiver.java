package CommandReceivers;

import CommandControllers.CommandSQL;
import Manager.AddressAnalyser;
import Manager.LinesManager;
import Mode.Mode;

import java.util.LinkedList;
import java.util.List;

import static Manager.AddressAnalyser.listToFile;

/*
(.,.)s[/str1/str2/count]
	(.,.)s[/str1/str2/g]

(.,.)s		在指定行用str2替换str1。当最后为count（正整数）时，
	            对指定的每一行，替换第count个匹配的str1（若该行没有，则不替换），
	            若不指定，即(.,.)s/str1/str2/，默认每一行替换第一个。

	            当最后为g时，替换所有。当指定行没有符合要求的或没有第count个时，输出'?'。
	            (.,.)s重复上一次替换命令，当前行被设为最后一个被改变的行。

* */
public class s_receiver extends ReceiverAdapter {
    private int currentLine;
    private LinesManager editorLineManager;
    private boolean findSymbol = false;

    public s_receiver(CommandSQL commandSQL) {
        super(commandSQL);
        Initialize(commandSQL);
    }

    @Override
    public void doAction() {
        this.commandSQL.setMode(Mode.Command);
        /*
         * Deal with the (.,.)
         * */
        int[] tmpArr = AddressAnalyser.getLineRange(commandSQL, editorLineManager, currentLine);
        int beginIndex = tmpArr[0];
        int endIndex = tmpArr[1];
        try {
            replaceStrings(beginIndex, endIndex, commandSQL.getRearList());
        } catch (IndexOutOfBoundsException e) {
            System.out.println("?");
            e.printStackTrace();
        }
    }

    @Override
    public void reverseAction() {

    }

    private void replaceStrings(int beginIndex, int endIndex, List<String> rearList)
            throws IndexOutOfBoundsException {

        List<String> targetList = editorLineManager.getLines().subList(beginIndex - 1, endIndex);
        List<String> result = new LinkedList<>();
        String count;
        String orignStr = rearList.get(0);
        String newStr = rearList.get(1);
        if (rearList.size() == 2)
            count = "1";
        else {
            count = rearList.get(2);
        }
        for (String target : targetList) {
            if (count.equals("g"))
                result = g_replace(result, orignStr, newStr, target);
            else {
                result = normalReplace(result, count, orignStr, newStr, target);
            }
        }
        if (!findSymbol)
            throw new IndexOutOfBoundsException();
        mergeIn(editorLineManager.getLines(), result, beginIndex, endIndex);
    }

    private List<String> normalReplace(List<String> result, String count, String orignStr, String newStr, String target) {
        int targetCount = Integer.parseInt(count);
        //分割
        String[] strings = target.split(orignStr);
        //含有的orignStr个数为len-1
        if (strings.length - 1 < targetCount) {
            result.add(target);
        } else {

            StringBuilder stringBuilder = new StringBuilder();
            for (int index = 0; index < strings.length; index++) {
                String tmp = strings[index];
                if (index + 1 == targetCount)
                    stringBuilder.append(tmp + newStr);
                else if (index == strings.length - 1)
                    stringBuilder.append(tmp);
                else
                    stringBuilder.append(tmp + orignStr);
            }
            result.add(stringBuilder.toString());
            this.findSymbol = true;
        }
        return result;
    }

    private List<String> g_replace(List<String> result, String orignStr, String newStr, String target) {
        if (target.split(orignStr).length == 1) {
            result.add(target);
        } else {
            result.add(target.replaceAll(orignStr, newStr));
            this.findSymbol = true;
        }
        return result;
    }

    private void mergeIn(List<String> lines, List<String> insert, int beginIndex, int endIndex) {
        int linesLen = lines.size();
        List<String> result = new LinkedList<>();
        result.addAll(lines.subList(0, beginIndex - 1));
        result.addAll(insert);
        result.addAll(lines.subList(endIndex, linesLen));
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
