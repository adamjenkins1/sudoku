var board = [
  , , ,4, ,8, ,2,9
  , , , , , , , , ,4
  ,8,5, , ,2, , , ,7
  , , ,8,3,7,4,2, ,
  , ,2, , , , , , ,
  , , ,3,2,6,1,7, ,
  , , , , ,9,3,6,1,2
  ,2, , , , , ,4, ,3
  ,1,3, ,6,4,2, ,7,undefined
]
var mySudokuJS = $("#sudoku").sudokuJS({
  board: board
  //difficulty: "medium"
});

//mySudokuJS.setBoard(board);

$('#solve').on('click', function () {
  mySudokuJS.solveAll();
});

