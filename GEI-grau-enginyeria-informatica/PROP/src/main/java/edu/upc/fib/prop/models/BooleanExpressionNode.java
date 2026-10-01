package edu.upc.fib.prop.models;

import edu.upc.fib.prop.utils.Constants;

import java.util.*;

public class BooleanExpressionNode {

    private Operator operator;
    private NodeType nodeType;
    private String word;
    private ArrayList<BooleanExpressionNode> children;

    public BooleanExpressionNode(){
        this.children = new ArrayList<>();
    }

    private BooleanExpressionNode(NodeType nodeType, String word) {
        this.nodeType = nodeType;
        this.word = word;
        this.children = new ArrayList<>();
    }

    private void copy(BooleanExpressionNode node){
        this.operator = node.operator;
        this.nodeType = node.nodeType;
        this.word = node.word;
        this.children = node.children;
    }

    public Operator getOperator() {
        return operator;
    }

    public NodeType getNodeType() {
        return nodeType;
    }

    public String getWord() {
        return word;
    }

    public ArrayList<BooleanExpressionNode> getChildren() {
        return children;
    }

    public void generateTree(String expression) {
        BooleanExpressionNode child;
        int open, start;
        for (int i = 0; i < expression.length(); ++i) {
            if (expression.charAt(i) == '(') {
                child = new BooleanExpressionNode();
                ++i;
                start = i;
                open = 1;
                while (i < expression.length() && open != 0) {
                    if (expression.charAt(i) == '(') {
                        ++open;
                    } else if (expression.charAt(i) == ')') {
                        --open;
                    }
                    ++i;
                }
                child.generateTree(expression.substring(start, i - 1));
                this.children.add(child);
            } else if (expression.charAt(i) == '{') {
                start = ++i;
                while (i < expression.length() && expression.charAt(i) != '}') {
                    ++i;
                }
                String[] words = expression.substring(start, i).split(Constants.WORD_SEPARATION_REGEX);
                child = new BooleanExpressionNode();
                child.operator = Operator.AND;
                for (String word : words) { // Add words
                    child.children.add(new BooleanExpressionNode(NodeType.WORD, word));
                }
                this.children.add(child);
            } else if (expression.charAt(i) == '&' || expression.charAt(i) == '|') {
                Operator op = (expression.charAt(i) == '&') ? Operator.AND : Operator.OR;
                if(this.operator == null) this.operator = op;
                else if(this.operator != op) {
                    child = new BooleanExpressionNode();
                    child.copy(this);
                    this.children = new ArrayList<>();
                    this.operator = op;
                    i++;
                    while(expression.charAt(i) == ' ') ++i;
                    start = i;
                    BooleanExpressionNode child2 = new BooleanExpressionNode();
                    char end = getEndChar(expression.charAt(i++));
                    while (i < expression.length() && expression.charAt(i) != end) {
                        ++i;
                    }
                    if (end == ' ' && i >= expression.length()) --i;
                    child2.generateTree(expression.substring(start, i+1));
                    this.children.add(child);
                    this.children.add(child2);
                    if (end == ' ' && i >= expression.length()) ++i;
                }
            } else if (expression.charAt(i) == '"') {
                start = ++i;
                while (i < expression.length() && expression.charAt(i) != '"') {
                    ++i;
                }
                String word = expression.substring(start, i);
                this.children.add(new BooleanExpressionNode(NodeType.SENTENCE, word));
            } else if (expression.charAt(i) == '!'){
                child = new BooleanExpressionNode();
                BooleanExpressionNode grandchild = new BooleanExpressionNode();
                child.operator = Operator.NOT;
                start = ++i;
                char end = getEndChar(expression.charAt(i++));
                while(i < expression.length() && expression.charAt(i) != end) {
                    ++i;
                }
                if (end == ' ' && i >= expression.length()) --i;
                grandchild.generateTree(expression.substring(start,i+1));
                if (end == ' ' && i >= expression.length()) ++i;
                child.children.add(grandchild);
                this.children.add(child);
            } else if (expression.charAt(i) != ' ') {
                start = i++;
                while (i < expression.length() && expression.charAt(i) != ' ') {
                    ++i;
                }
                String word = expression.substring(start, i);
                this.children.add(new BooleanExpressionNode(NodeType.WORD, word));
            }

        }

        if (this.children.size() == 1 && this.operator != Operator.NOT) {
            this.copy(this.children.get(0));
        }

    }

    private char getEndChar(char start) {
        switch (start) {
            case '{':
                return '}';
            case '"':
                return '"';
            case '(':
                return ')';
            default:
                return ' ';
        }
    }

}
