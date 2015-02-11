#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct User
{
	int user_id;
	int* scores;
	bool can_print;
	int count_solved;

	int total_score;
};

int main()
{
	int number_of_users, number_of_problems, number_of_submittions;
	scanf("%d%d%d",  &number_of_users, &number_of_problems, &number_of_submittions);
	int *full_mark = new int[number_of_problems + 1];
	User *users = new User[number_of_users + 1];
	// 初始化user列表
	for(int i = 1; i <= number_of_users; ++i)
	{
		users[i].user_id = i;
		users[i].scores = new int[number_of_problems + 1];
		for(int j = 1; j <= number_of_problems; ++j)
			users[i].scores[j] = -1;
		users[i].can_print = false;
		users[i].count_solved = 0;
	}
	for(int i = 1; i <= number_of_problems; ++i)
		scanf("%d", full_mark + i);
	// 提交
	for(int i = 1; i <= number_of_submittions; ++i)
	{
		int user_id, problem_id, partial_score_obtained;
		scanf("%d%d%d", &user_id, &problem_id, &partial_score_obtained);
		if(partial_score_obtained == -1)
			partial_score_obtained = 0;
		else
			users[user_id].can_print = true;
		if(partial_score_obtained <= users[user_id].scores[problem_id]) 
			continue;
		if(partial_score_obtained == full_mark[problem_id]) 
			++(users[user_id].count_solved);
		users[user_id].scores[problem_id] = partial_score_obtained;
	}
	// 统计总分
	for(int i = 1; i <= number_of_users; ++i)
	{
		int total_score = 0;
		for(int j = 1; j <= number_of_problems; ++j)
		{
			int score = users[i].scores[j];
			if(score == -1) continue;
			total_score += score;
		}
		users[i].total_score = total_score;
	}
	// 排名
	sort(users + 1, users + number_of_users + 1, [](const User &a, const User &b)
	{ 
		if(a.total_score == b.total_score)
		{
			if(a.count_solved == b.count_solved)
				return a.user_id < b.user_id;
			return a.count_solved > b.count_solved;
		}
		return a.total_score > b.total_score;
	});
	// 输出
	int rank = 1;
	for(int i = 1; i <= number_of_users; ++i)
	{
		if(i > 1 && users[i].total_score < users[i - 1].total_score)
			rank = i;
		if(!users[i].can_print) continue;
		printf("%d %05d %d", rank, users[i].user_id, users[i].total_score);
		for(int j = 1; j <= number_of_problems; ++j)
		{
			if(users[i].scores[j] == -1)
				printf(" -");
			else
				printf(" %d", users[i].scores[j]);
		}
		printf("\n");
	}
	return 0;
}