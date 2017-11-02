function retryForever(fn) {
  try {
    var val = fn();
    if(val == true) {
      $('#loading').slideUp();
      $('#solveButton').show();
      return;
    }
  } catch (err) {
    console.log('retry...');
    return retryForever(fn);
  }
}

function tryGeneratingBoard() {
  var size = 9;
  var mySudokuJS = $("#sudoku").sudokuJS({
    boardSize: size,
    difficulty: "medium"
  });

  $('#solve').on('click', function() {
    var board = mySudokuJS.getBoard();
    var arrayBoard = board.map(function(obj) {
      return obj.val;
    });
    console.log(board);
    console.log(arrayBoard);
    mySudokuJS.solveAll();
    console.log(mySudokuJS);
  });
  return true;
}

retryForever(tryGeneratingBoard)
