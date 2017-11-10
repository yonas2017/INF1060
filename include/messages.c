#include <messages.h>

uint8_t getJobType(char JobType)
{
	switch(JobType)
	{
		case 'O':
			return 0;
		case 'E':
			return 1;
		case 'Q':
			return 7;
		default:
			printf("Wrong Job Type\n");
			break;
	}
}

uint8_t computeChecksum(
	unsigned int jobTextLength,
	char* JobTekst
)
{
	int j;
	uint8_t checkSum = 0;
	for(j = 0; j < jobTextLength - 1; jobTextLength++)
	{
		checkSum += ((uint8_t) JobTekst[j] % 32);
	}

	printf("checkSum = %d\n", checkSum);
	return checkSum;
}

unsigned char getJobInfo(
	char JobType,
	unsigned int jobTextLength,
	char* JobTekst
)
{
	uint8_t jobInfo = (getJobType(JobType)<<5) |
										(computeChecksum(jobTextLength, JobTekst) & 0x1F);
	return jobInfo;
}
