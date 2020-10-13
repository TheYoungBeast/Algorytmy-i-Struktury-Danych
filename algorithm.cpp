#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream Input("input.txt");
	std::string Line;

	getline(Input, Line);
	unsigned AmountOfData = std::stoi(Line);

	std::vector< std::pair<int, int> > Intervals;

	while (getline(Input, Line))
	{
		std::istringstream lstream(Line);

		while (lstream)
		{
			std::string sub1, sub2;
			lstream >> sub1;
			lstream >> sub2;

			if (sub1.empty() || sub2.empty())
				continue;

			Intervals.push_back(std::make_pair(std::stoi(sub1), std::stoi(sub2)));
		}
	}

	std::sort(Intervals.begin(), Intervals.end()); // dzięki sortowaniu problem można rozwiązać liniowo

	std::vector< std::pair<int, int> > Results;
	Results.push_back(Intervals[0]);

	for (size_t j, i = 0; i < Intervals.size(); i++)
	{
		for (j = (i + 1); j < Intervals.size(); j++, i++) // inkrementowanie i, j (j=i+1) co sprawia, że algorytm staje się liniowy ZŁOŻONOŚĆ O(n-1)
		{
			if (Results[Results.size() - 1].second >= Intervals[j].first)
			{
				if (Intervals[j].second > Results[Results.size() - 1].second)
					Results[Results.size() - 1].second = Intervals[j].second;
			}
			else if (Intervals[j].first > Results[Results.size() - 1].second)
				break;
		}

		if (j < Intervals.size()) Results.push_back(Intervals[j]);
	}

	std::ofstream Output("output.txt");
	Output << Results.size() << std::endl;

	for (auto &x : Results)
		Output << x.first << " " << x.second << std::endl;

	Output.close();

	return 0;
}
