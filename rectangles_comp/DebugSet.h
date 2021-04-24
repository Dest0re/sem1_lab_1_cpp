#pragma once
class DebugSet
{
	double*** datasets;
	int results[5];

	void edit_line(double* line, double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7) {
		line[0] = v0;
		line[1] = v1;
		line[2] = v2;
		line[3] = v3;
		line[4] = v4;
		line[5] = v5;
		line[6] = v6;
		line[7] = v7;
	}

	DebugSet() {
		datasets = new double** [5];
		for (int s = 0; s < 5; s++) {
			datasets[s] = new double* [5];
			for (int r = 0; r < 2; r++) {
				datasets[s][r] = new double[8];
			}
		}

		// 1,  один пересекает грань другого

		edit_line(datasets[0][0], 0, 0, 4, 0, 4, 3, 0, 3);
		edit_line(datasets[0][0], 3, 1, 5, 1, 5, 2, 3, 2);
		results[0] = 1;

		// 2,  оба заданы некорректно

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		results[1] = -1;

		// 3,  один внутри другого

		edit_line(datasets[0][0], 0, 0, 6, 0, 6, 5, 0, 5);
		edit_line(datasets[0][0], 2, 1, 5, 1, 5, 4, 2, 4);
		results[2] = 1;

		// 4,  пересекаются гранью

		edit_line(datasets[0][0], 0, 0, 5, 0, 5, 5, 0, 5);
		edit_line(datasets[0][0], 5, 0, 7, 0, 7, 5, 5, 5);
		results[3] = 1;


		// 5,  не пересекаются

		edit_line(datasets[0][0], 0, 0, 3, 0, 3, 3, 0, 3);
		edit_line(datasets[0][0], 6, 0, 9, 0, 9, 3, 6, 3);
		results[4] = 0;
	}


	~DebugSet() {
		for (int s = 0; s < 5; s++) {
			for (int r = 0; r < 2; r++) {
				delete[] datasets[s][r];
			}
			delete[] datasets[s];
		}
		delete[] datasets;
	}
};
