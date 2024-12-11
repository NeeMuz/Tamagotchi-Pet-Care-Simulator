using System;
using System.Collections.Generic;
using System.Threading;

public class Tamagotchi
{
    public event Action Feed;
    public event Action Walk;
    public event Action Sleep;
    public event Action Heal;
    public event Action Play;

    private static readonly Random Random = new Random();
    private int hunger = 0;
    private int actionCounter = 0;

    public void Run()
    {
        Console.Clear();
        while (true)
        {
            Thread.Sleep(500);
            actionCounter++;
            GenerateRandomRequest();
        }
    }

    private void GenerateRandomRequest()
    {
        var actions = new List<Action> { FeedAction, WalkAction, SleepAction, PlayAction };

        var action = actions[Random.Next(actions.Count)];
        action.Invoke();
    }

    private void FeedAction() => HandleAction(Feed, ref hunger, "feed");
    private void WalkAction() => HandleAction(Walk, ref hunger, "take a walk");
    private void SleepAction() => HandleAction(Sleep, ref hunger, "put to sleep");
    private void PlayAction() => HandleAction(Play, ref hunger, "play");

    private void HandleAction(Action action, ref int counter, string request)
    {
        Console.Clear();
        Console.WriteLine($"Tamagotchi asks: {request}.");
        Console.WriteLine("");
        action?.Invoke();
        counter++;
    }

    static void Main()
    {
        var tamagotchi = new Tamagotchi();
        tamagotchi.Feed += () => Console.WriteLine("Fed.");
        tamagotchi.Walk += () => Console.WriteLine("Walked.");
        tamagotchi.Sleep += () => Console.WriteLine("Sleeping.");
        tamagotchi.Heal += () => Console.WriteLine("Healed.");
        tamagotchi.Play += () => Console.WriteLine("Playing.");

        tamagotchi.Run();
    }
}
