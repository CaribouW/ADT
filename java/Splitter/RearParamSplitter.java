package Splitter;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * The rearParam is relatively simple and we could split the param easily
 *
 * @author lfm
 * @time 5.22
 */
public class RearParamSplitter {
    private String rearParam;
    private String middleCommand;
    private List<String> rearParamList = new ArrayList<>();

    public RearParamSplitter(CommandSplitter commandSplitter) {
        this.middleCommand = commandSplitter.getMiddleCommand();
        this.rearParam = commandSplitter.getRearParam();
    }

    public void doRearSplit() {
        if (rearParam.equals("") || rearParam.length() == 1) {
            rearParamList.add(rearParam);
            return;
        }
        /*
         * 特殊情况 /str1/str2/  之后读取时只需考虑列表size是否大于一即可
         * */
        String tmp = this.rearParam;
        if (this.middleCommand.equals("s")) {
            String[] strArr = tmp.substring(1).split("/"); //小细节 subString(1) 避免产生""
            rearParamList.addAll(Arrays.asList(strArr));
        } else
            rearParamList.add(rearParam);
    }

    public List<String> getRearParamList() {
        return rearParamList;
    }

    public static void main(String[] args) {
        CommandSplitter commandSplitter = new CommandSplitter("a33");
        commandSplitter.doSplitCommand();
        RearParamSplitter rearParamSplitter = new RearParamSplitter(commandSplitter);

        rearParamSplitter.doRearSplit();
        System.out.println(rearParamSplitter.getRearParamList());
    }
}
