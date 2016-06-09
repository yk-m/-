
void setAmida(char map[][MAX_ARRAY], int row, int column)
{
	int i,j;
	row++;
	column++;
	for(i=0; i<row; i++) {
		for(j=0; j<column; j++) {
			if (j%2 == 0) {
				map[i][j] = '|';
			} else {
				map[i][j] = ' ';
			}
		}
		map[i][column] = '\0';
	}
	for(j=0; j<=column; j++) {
		map[row][j] = '\0';
	}
}