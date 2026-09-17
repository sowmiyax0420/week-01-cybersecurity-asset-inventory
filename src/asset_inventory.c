#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ASSETS 100

typedef struct {
    char assetID[20];
    char assetName[50];
    char assetType[20];
    char ipAddress[30];
    char operatingSystem[50];
    char department[50];
    char riskLevel[20];
    char securityStatus[20];
} Asset;

Asset assets[MAX_ASSETS];
int assetCount = 0;

/* ---------- Input Helper ---------- */

void readString(char *str, int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

/* ---------- Validation ---------- */

int validAssetType(char *type)
{
    return strcmp(type, "Workstation") == 0 ||
           strcmp(type, "Server") == 0 ||
           strcmp(type, "Router") == 0 ||
           strcmp(type, "Switch") == 0 ||
           strcmp(type, "Application") == 0;
}

int validRiskLevel(char *risk)
{
    return strcmp(risk, "Low") == 0 ||
           strcmp(risk, "Medium") == 0 ||
           strcmp(risk, "High") == 0 ||
           strcmp(risk, "Critical") == 0;
}

int validSecurityStatus(char *status)
{
    return strcmp(status, "Secure") == 0 ||
           strcmp(status, "Warning") == 0 ||
           strcmp(status, "Vulnerable") == 0;
}

/* ---------- Find Asset ---------- */

int findAsset(char *id)
{
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(assets[i].assetID, id) == 0)
            return i;
    }

    return -1;
}

/* ---------- Add Asset ---------- */

void addAsset()
{
    Asset a;

    if (assetCount >= MAX_ASSETS)
    {
        printf("\nAsset storage is full!\n");
        return;
    }

    printf("\n========== ADD ASSET ==========\n");

    printf("Asset ID: ");
    readString(a.assetID, sizeof(a.assetID));

    if (findAsset(a.assetID) != -1)
    {
        printf("Asset ID already exists!\n");
        return;
    }

    printf("Asset Name: ");
    readString(a.assetName, sizeof(a.assetName));

    printf("Asset Type (Workstation/Server/Router/Switch/Application): ");
    readString(a.assetType, sizeof(a.assetType));

    if (!validAssetType(a.assetType))
    {
        printf("Invalid Asset Type!\n");
        return;
    }

    printf("IP Address: ");
    readString(a.ipAddress, sizeof(a.ipAddress));

    printf("Operating System: ");
    readString(a.operatingSystem, sizeof(a.operatingSystem));

    printf("Department: ");
    readString(a.department, sizeof(a.department));

    printf("Risk Level (Low/Medium/High/Critical): ");
    readString(a.riskLevel, sizeof(a.riskLevel));

    if (!validRiskLevel(a.riskLevel))
    {
        printf("Invalid Risk Level!\n");
        return;
    }

    printf("Security Status (Secure/Warning/Vulnerable): ");
    readString(a.securityStatus, sizeof(a.securityStatus));

    if (!validSecurityStatus(a.securityStatus))
    {
        printf("Invalid Security Status!\n");
        return;
    }

    assets[assetCount] = a;
    assetCount++;

    printf("\nAsset added successfully!\n");
}

/* ---------- Display One Asset ---------- */

void displayAsset(Asset a)
{
    printf("\n----------------------------------------\n");
    printf("Asset ID : %s\n", a.assetID);
    printf("Asset Name : %s\n", a.assetName);
    printf("Asset Type : %s\n", a.assetType);
    printf("IP Address : %s\n", a.ipAddress);
    printf("OS : %s\n", a.operatingSystem);
    printf("Department : %s\n", a.department);
    printf("Risk Level : %s\n", a.riskLevel);
    printf("Status : %s\n", a.securityStatus);
    printf("----------------------------------------\n");
}

/* ---------- Display All Assets ---------- */

void displayAssets()
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets available.\n");
        return;
    }

    printf("\n========================================\n");
    printf(" CYBERSECURITY ASSET INVENTORY\n");
    printf("========================================\n");

    for (i = 0; i < assetCount; i++)
    {
        displayAsset(assets[i]);
    }
}

/* ---------- Search Asset ---------- */

void searchAsset()
{
    char id[20];
    int index;

    printf("\nEnter Asset ID to search: ");
    readString(id, sizeof(id));

    index = findAsset(id);

    if (index == -1)
    {
        printf("Asset not found!\n");
    }
    else
    {
        printf("\nAsset Found:\n");
        displayAsset(assets[index]);
    }
}

/* ---------- Update Asset ---------- */

void updateAsset()
{
    char id[20];
    int index;

    printf("\nEnter Asset ID to update: ");
    readString(id, sizeof(id));

    index = findAsset(id);

    if (index == -1)
    {
        printf("Asset not found!\n");
        return;
    }

    printf("\nEnter new details:\n");

    printf("Asset Name: ");
    readString(assets[index].assetName,
               sizeof(assets[index].assetName));

    printf("Asset Type: ");
    readString(assets[index].assetType,
               sizeof(assets[index].assetType));

    if (!validAssetType(assets[index].assetType))
    {
        printf("Invalid Asset Type!\n");
        return;
    }

    printf("IP Address: ");
    readString(assets[index].ipAddress,
               sizeof(assets[index].ipAddress));

    printf("Operating System: ");
    readString(assets[index].operatingSystem,
               sizeof(assets[index].operatingSystem));

    printf("Department: ");
    readString(assets[index].department,
               sizeof(assets[index].department));

    printf("Risk Level: ");
    readString(assets[index].riskLevel,
               sizeof(assets[index].riskLevel));

    if (!validRiskLevel(assets[index].riskLevel))
    {
        printf("Invalid Risk Level!\n");
        return;
    }

    printf("Security Status: ");
    readString(assets[index].securityStatus,
               sizeof(assets[index].securityStatus));

    if (!validSecurityStatus(assets[index].securityStatus))
    {
        printf("Invalid Security Status!\n");
        return;
    }

    printf("\nAsset updated successfully!\n");
}

/* ---------- Delete Asset ---------- */

void deleteAsset()
{
    char id[20];
    int index, i;

    printf("\nEnter Asset ID to delete: ");
    readString(id, sizeof(id));

    index = findAsset(id);

    if (index == -1)
    {
        printf("Asset not found!\n");
        return;
    }

    for (i = index; i < assetCount - 1; i++)
    {
        assets[i] = assets[i + 1];
    }

    assetCount--;

    printf("\nAsset deleted successfully!\n");
}

/* ---------- Security Summary ---------- */

void securitySummary()
{
    int critical = 0;
    int high = 0;
    int medium = 0;
    int vulnerable = 0;
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(assets[i].riskLevel, "Critical") == 0)
            critical++;

        if (strcmp(assets[i].riskLevel, "High") == 0)
            high++;

        if (strcmp(assets[i].riskLevel, "Medium") == 0)
            medium++;

        if (strcmp(assets[i].securityStatus, "Vulnerable") == 0)
            vulnerable++;
    }

    printf("\n========================================\n");
    printf(" SECURITY SUMMARY\n");
    printf("========================================\n");

    printf("Total Assets : %d\n", assetCount);
    printf("Critical Assets : %d\n", critical);
    printf("High Risk Assets : %d\n", high);
    printf("Medium Risk Assets : %d\n", medium);
    printf("Vulnerable Assets : %d\n", vulnerable);

    printf("========================================\n");
}

/* ---------- Main Menu ---------- */

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n========================================\n");
        printf(" CYBERSECURITY ASSET INVENTORY\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Update Asset\n");
        printf("5. Delete Asset\n");
        printf("6. Security Summary\n");
        printf("7. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addAsset();
                break;

            case 2:
                displayAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                updateAsset();
                break;

            case 5:
                deleteAsset();
                break;

            case 6:
                securitySummary();
                break;

            case 7:
                printf("\nThank you for using the system!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
