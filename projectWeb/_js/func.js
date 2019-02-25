function insertionSort(vector, n:int)
{
	var auxiliar;
	var j : int;
	for (var i = 0; i < n; i++) {
		auxiliar = vector[i];
		for (var j = i; (j > 0 && auxiliar < vector[j - 1]); j--) {
			vector[j] = vector[j - 1];
		};
		vector[i] = auxiliar;
	};
}