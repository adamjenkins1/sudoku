function retryForever(fn) {
  var sizes = [4, 9, 16];
  var diffs = ["easy", "medium", "hard", "very hard"];
  var i = 0, j = 0;
  for(i = 0; i < sizes.length; i++) {
    for(j = 0; j < diffs.length; j++) {
      try {
        fn(sizes[i], diffs[j]);
      } 
      catch (err) {
        console.log(err);
        console.log('retry...');
        fn(sizes[i], diffs[j]);
      }
    }
  }
}

function getShortDiff(diff) {
  if(diff == "easy")
    return "e";
  else if(diff == "medium")
    return "m";
  else if(diff == "hard")
    return "h";
  else if(diff == "very hard")
    return "vh";
}

function tryGeneratingBoard(size, diff) {
  // size = {4, 9, 16}
  // difficulty = {"easy", "medium", "hard", "very hard"}
  console.log("size = " + size + ", difficulty = " + diff);

  var mySudokuJS = $("#sudoku").sudokuJS({
    boardSize: size,
    difficulty: diff
  });

  var board = mySudokuJS.getBoard();
  var arrayBoard = board.map(function(obj) {
    return obj.val;
  });


  var i = 0;
  for(i = 0; i < arrayBoard.length; i++) {
    if(arrayBoard[i] == null) {
      arrayBoard[i] = 0;
    }
  }

  var shortDiff = getShortDiff(diff);
  var url = "/" + size + "/" + shortDiff + "/save/";
  $.post(url, {board: arrayBoard})
    .done(function(result) {
      console.log(arrayBoard.join(' '));
      console.log(result);
    })
  .fail(function(xhr, status, error) {
    console.log(xhr);
    console.log(status);
    console.log(error);
  });
  return true;
}

function csrfSafeMethod(method) {
  return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

$.ajaxSetup({
  beforeSend: function(xhr, settings) {
    if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
      xhr.setRequestHeader("X-CSRFToken", csrftoken);
    }
  }
});
retryForever(tryGeneratingBoard);
