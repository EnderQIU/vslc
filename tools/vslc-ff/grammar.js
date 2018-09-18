let Grammar = require('first-follow').Grammar;

let grammar = new Grammar([
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
        right: ["b", "A'"]
    },
    {
        left: "A'",
        right: [null]
    },
    {
        left: "B",
        right: ["a", "b", "(", "c", ")", "D"]
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
        right: ["b", "c", "L"]
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
        right: ["J'"]
    },
    {
        left: "J'",
        right: ["i", "M", "j", "D"]
    },
    {
        left: "J'",
        right: ["i", "M", "j", "D", "l", "D", "K"]
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
]);

console.log("=====================");
console.log("FIRST SETS");
console.log("=====================");
console.log(grammar.getFirstSets());
console.log("=====================");
console.log("FOLLOW SETS");
console.log("=====================");
console.log(grammar.getFollowSets());
console.log("=====================");
console.log("PREDICT SETS");
console.log("=====================");
console.log(grammar.getPredictSets());
console.log("=====================");