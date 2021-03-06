let Grammar = require('first-follow').Grammar;

const productions = [
    {
        left: "S",
        right: ["A"]
    },
    {
        left: "A",
        right: ["B", "A'"]
    },
    {
        left: "A'",
        right: ["B", "A'"]
    },
    {
        left: "A'",
        right: [null]
    },
    {
        left: "B",
        right: ["a", "b", "(", "C", ")", "D"]
    },
    {
        left: "C",
        right: ["E"]
    },
    {
        left: "C",
        right: [null]
    },
    {
        left: "E",
        right: ["b", "E'"]
    },
    {
        left: "E'",
        right: [",", "b", "E'"]
    },
    {
        left: "E'",
        right: [null]
    },
    {
        left: "D",
        right: ["F"]
    },
    {
        left: "D",
        right: ["G"]
    },
    {
        left: "D",
        right: ["H"]
    },
    {
        left: "D",
        right: ["I"]
    },
    {
        left: "D",
        right: ["J"]
    },
    {
        left: "D",
        right: ["K"]
    },
    {
        left: "D",
        right: ["L"]
    },
    {
        left: "F",
        right: ["b", "c", "M"]
    },
    {
        left: "M",
        right: ["V", "M'"]
    },
    {
        left: "M'",
        right: ["+", "V", "M'"]
    },
    {
        left: "M'",
        right: ["-", "V", "M'"]
    },
    {
        left: "M'",
        right: [null]
    },
    {
        left: "V",
        right: ["W", "V'"]
    },
    {
        left: "V'",
        right: ["*", "W", "V'"]
    },
    {
        left: "V'",
        right: ["/", "W", "V'"]
    },
    {
        left: "V'",
        right: [null]
    },
    {
        left: "W",
        right: ["(", "M", ")"]
    },
    {
        left: "W",
        right: ["d"]
    },
    {
        left: "W",
        right: ["b", "W'"]
    },
    {
        left: "W'",
        right: ["(", "N", ")"]
    },
    {
        left: "W'",
        right: [null]
    },
    {
        left: "N",
        right: [null]
    },
    {
        left: "N",
        right: ["O"]
    },
    {
        left: "O",
        right: ["M", "O'"]
    },
    {
        left: "O'",
        right: [",", "M", "O'"]
    },
    {
        left: "O'",
        right: [null]
    },
    {
        left: "H",
        right: ["e", "P"]
    },
    {
        left: "P",
        right: ["Q", "P'"]
    },
    {
        left: "P'",
        right: [",", "Q", "P'"]
    },
    {
        left: "P'",
        right: [null]
    },
    {
        left: "Q",
        right: ["M"]
    },
    {
        left: "Q",
        right: ["f"]
    },
    {
        left: "G",
        right: ["g", "M"]
    },
    {
        left: "I",
        right: ["h"]
    },
    {
        left: "J",
        right: ["i", "M", "j", "D", "J'"]
    },
    {
        left: "J'",
        right: ["k"]
    },
    {
        left: "J'",
        right: ["l", "D", "k"]
    },
    {
        left: "K",
        right: ["m", "M", "n", "D", "o"]
    },
    {
        left: "L",
        right: ["{", "R", "T", "}"]
    },
    {
        left: "R",
        right: ["R'"]
    },
    {
        left: "R'",
        right: ["U", "R'"]
    },
    {
        left: "R'",
        right: [null]
    },
    {
        left: "U",
        right: ["p", "E"]
    },
    {
        left: "T",
        right: ["D", "T'"]
    },
    {
        left: "T'",
        right: ["D", "T'"]
    },
    {
        left: "T'",
        right: [null]
    }
]

let grammar = new Grammar(productions);

// console.log("=====================");
// console.log("FIRST SETS");
// console.log("=====================");
// console.log(grammar.getFirstSets());
// console.log("=====================");
// console.log("FOLLOW SETS");
// console.log("=====================");
// console.log(grammar.getFollowSets());
// console.log("=====================");
// console.log("PREDICT SETS");
// console.log("=====================");
// console.log(grammar.getPredictSets());
// console.log("=====================");

let select_set = grammar.getPredictSets();

for (let i = 0; i<productions.length; i++) {
    let production_right = "";
    for (let s of productions[i].right) production_right+=s;
    console.log("SELECT("+productions[i].left+" -> "+production_right.toString().replace("null", "ε")+") = {" + select_set[(i+1).toString()].toString()+"}");
}