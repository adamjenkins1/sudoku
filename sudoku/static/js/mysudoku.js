function retryForever(fn) {
  try {
    var val = fn();
    if(val == true) {
      $('#loading').slideUp();
      $('#solveButton').show();
      return;
    }
  } catch (err) {
    console.log(err);
    console.log('retry...');
    return retryForever(fn);
  }
}

function tryGeneratingBoard() {
  // size = {4, 9, 16}
  // difficulty = {"easy", "medium", "hard", "very hard"}
  error = false;
  errorMsg = "\n";
  if(!(size == 4 || size == 9 || size == 16)) {
    error = true;
    errorMsg += "Invalid board size: " + size + ". Defaulting to size 9.\n";
    size = 9;
  }
  
  if(!(diff == "easy" || diff == "medium" || diff == "hard" 
        || diff == "very hard")) {
    error = true;
    errorMsg += "Invalid difficulty: " + diff + ". Defaulting to medium.\n";
    diff = "medium";
    shortDiff = "m";
  }
  
  if(error == true) {
    alert(errorMsg);
    $(location).attr('href', '/' + size + '/' + shortDiff + '/'); 
  }

  var mySudokuJS = $("#sudoku").sudokuJS({
    boardSize: size,
    difficulty: diff
  });

  $('#solve').on('click', function() {
    var board = mySudokuJS.getBoard();
    var arrayBoard = board.map(function(obj) {
      return obj.val;
    });

    for(i = 0; i < arrayBoard.length; i++) {
      if(arrayBoard[i] == null) {
        arrayBoard[i] = 0;
      }
    }

    mySudokuJS.solveAll();
    console.log(arrayBoard);
    console.log(arrayBoard.join(" "));
    console.log(mySudokuJS);
  });
  return true;
}

retryForever(tryGeneratingBoard)
