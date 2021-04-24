#pragma once
class DebugSet
{
	double*** datasets;

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

		// 1

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		

		// 2

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);

		// 3

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);

		// 4

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);


		// 5

		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
		edit_line(datasets[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
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
