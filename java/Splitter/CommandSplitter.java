package Splitter;


/**
 * Split and analyse the command from the console
 * Split the command line into address/middleCommand/RearParam.
 *
 * @author lfm
 * @time 5.22
 */
public class CommandSplitter {
    private String commandLine = "";
    private String address = "";
    private String middleCommand = "";
    private String RearParam = "";

    public CommandSplitter(String commandLine) {
        this.commandLine = commandLine;
    }


    public String getCommandLine() {
        return commandLine;
    }

    /**
     * We have to classify all of the structures of the commands and split them.
     */
    public void doSplitCommand() {
        String tmp = this.commandLine;
        int len = commandLine.length();
        /*
         * 高级命令和单字符命令处理
         * */
        if (len == 1) {
            singleChar_split(commandLine);
            return;
        } else if (len >= 2 && tmp.charAt(len - 2) == 'k') {
            k_split(this.commandLine);
            return;
        }
        /*
         *f w W 处理
         * */
        String[] newStrArr = tmp.split(" ");
        //含有空格
        if (newStrArr.length > 1) {
            Blank_split(tmp);
            return;
        }


        /*
         * s指令处理
         *复杂在于地址位也会有/
         * 先暂时默认/str/在地址位只出现一次.
         * 需要判定这些/ 符号是否是在Rear中的。
         * */
        int tmpIndex = commandLine.indexOf("/");
        if (tmpIndex == 0) {
            int index = 1;
            while (commandLine.charAt(index) != '/') {
                index++;
            }
            this.middleCommand = String.valueOf(commandLine.charAt(index + 1));
            this.address = commandLine.substring(0, index + 1);
            if (index < len - 2)
                this.RearParam = commandLine.substring(index + 2);
            return;

        } else if (tmpIndex > 0 && commandLine.charAt(tmpIndex - 1) == 's') {
            newStrArr = tmp.split("/");
            //含有 '/'或最后一个字符为s
            if (tmp.charAt(len - 1) == 's' || newStrArr.length > 1) {
                s_split(commandLine);
                return;
            }
        }

        /*
         * 其他指令处理
         * */
        normalSplit(commandLine);
    }

    public void setCommandLine(String commandLine) {
        this.commandLine = commandLine;
    }

    public String getAddress() {
        return address;
    }

    public String getMiddleCommand() {
        return middleCommand;
    }

    public String getRearParam() {
        return RearParam;
    }

    private void normalSplit(String commandLine) {
        int len = commandLine.length();
        int index = len - 1;
        //从后向前循环查找，直到第一个非数字元素，则为middleCommand
        while (index >= 0 && String.valueOf(commandLine.charAt(index)).matches("[0-9]")) {
            index--;
        }
        this.address = commandLine.substring(0, index);
        this.middleCommand = String.valueOf(commandLine.charAt(index));
        if (index < len - 1)
            this.RearParam = commandLine.substring(index + 1);
    }

    /**
     * @param commandLine :The command is related to the s.
     */
    private void s_split(String commandLine) {
        int len = commandLine.length();
        this.middleCommand = "s";
        if (commandLine.charAt(len - 1) == 's') {
            this.address = commandLine.substring(0, len - 1);
            this.RearParam = "";
        } else {
            int firstFileIndex = commandLine.indexOf('/');
            this.address = commandLine.substring(0, firstFileIndex - 1);
            this.RearParam = commandLine.substring(firstFileIndex);
        }
    }

    /**
     * @param str :The str that has one blank
     */
    private void Blank_split(String str) {
        int blankIndex = str.lastIndexOf(' ');
        this.RearParam = str.substring(blankIndex + 1);
        this.middleCommand = String.valueOf(str.charAt(blankIndex - 1));
        this.address = str.substring(0, blankIndex - 1);
    }

    /**
     * @param commandLine:The commandLine that is belong to the k command.
     */
    private void k_split(String commandLine) {
        int len = commandLine.length();
        int lastIndexOf_k = commandLine.lastIndexOf('k');
        this.address = commandLine.substring(0, lastIndexOf_k);
        this.middleCommand = "k";
        this.RearParam = String.valueOf(commandLine.charAt(len - 1));
    }

    /**
     * @param commandLine :The length of the command =1
     */
    private void singleChar_split(String commandLine) {
        this.address = "";
        this.middleCommand = commandLine;
        this.RearParam = "";
    }
}
