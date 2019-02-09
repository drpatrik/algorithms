import random
import time
import operator

CARDS = ['NOT USED', 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven',
         'Eight', 'Nine', 'Ten', 'Knight', 'Queen', 'King', 'Ace']


class Player:
    def __init__(self, name):
        self.hand = []
        self.name = name
        self.books = []

    def give(self, card):
        self.hand.append(card)
        return self.has_book(card)

    def card(self):
        if len(self.hand) == 0:
            return None
        hist = {}
        for c in self.hand:
            hist[c] = hist.get(c, 0) + 1
        hist = sorted(hist.items(), key=operator.itemgetter(1),
                      reverse=True)

        return hist[0][0]

    def add_cards(self, cards):
        for card in cards:
            self.hand.append(card)

        if not self.has_book(cards[0]):
            book = list(filter(lambda card: cards[0] == card, self.hand))
            print("Player %s: I now have %d %s\'s" %
                  (self.name, len(book), CARDS[cards[0]]))

    def has_book(self, new_card):
        self.hand.sort()
        book = list(filter(lambda card: new_card == card, self.hand))

        if len(book) == 4:
            print("Player %s: I got a book in %s\'s" %
                  (self.name, CARDS[new_card]))
            self.hand = [card for card in self.hand if new_card != card]
            self.books.append(book[0])
        return len(book) == 4

    def give_me_all_your(self, card):
        cards = []
        while card in self.hand:
            cards.append(card)
            self.hand.remove(card)
        return cards


def shuffle_and_give(names, cards_per_hand):
    deck_of_cards = [j for i in range(1, 5) for j in range(2, 15)]

    random.seed(time)
    random.shuffle(deck_of_cards)

    players = []
    for n in names:
        players.append(Player(n))

    random.shuffle(players)

    for i in range(0, cards_per_hand):
        for p in players:
            p.give(deck_of_cards.pop())

    return deck_of_cards, players


def pick_opponent(current_player, players):
    if len(players) == 2:
        return players[1] if current_player == players[0] else players[0]
    player = current_player
    while player == current_player:
        player = random.choice(players)
        if player.hand == 0:
            player = current_player
    return player


def check_hand(player, deck_of_cards):
    if len(player.hand) == 0 and len(deck_of_cards) > 0:
        player.give(deck_of_cards.pop())


def play_go_fish(names, cards_per_hand):
    deck_of_cards, players = shuffle_and_give(names, cards_per_hand)

    print("The following people participates:")
    for p in players:
        print(p.name)
    print("---- START ----")
    winners = []
    rounds = next_player = 0
    current_player = players[next_player]
    while len(players) > 1:
        rounds += 1
        opponent = pick_opponent(current_player, players)
        card = current_player.card()

        cards = []
        if card is None:
            print("Player %s: I have no cards" % current_player.name)
        else:
            print("Player %s: Please %s give me all your %s\'s" % (
                current_player.name, opponent.name, CARDS[card]))
            cards = opponent.give_me_all_your(card)
            check_hand(opponent, deck_of_cards)

        if len(cards) == 0:  # go fish
            if card:
                print("Player %s: Go fish" % opponent.name)
            has_pair = False
            if len(deck_of_cards) > 1:
                has_pair = current_player.give(deck_of_cards.pop())
            if not has_pair:
                next_player += 1
                if next_player >= len(players):
                    next_player = 0
                current_player = players[next_player]
            elif card:
                print('Player %s: Yippee I got a book, my turn again' %
                      current_player.name)
        else:
            print("Player %s: I have %d %s%s" %
                  (opponent.name, len(cards), CARDS[cards[0]],
                   "\'s" if len(cards) > 1 else ""))
            current_player.add_cards(cards)
            check_hand(current_player, deck_of_cards)

        for p in players:
            if len(p.hand) == 0 and len(deck_of_cards) == 0:
                winners.append(p)
                players.remove(p)

    winners.append(players[0])
    winners.sort(key=lambda player: len(player.books), reverse=True)

    print("---- DONE in %d round(s) ----' % rounds")
    for p in winners:
        print("%s got %d book(s) - %s" %
              (p.name, len(p.books), [CARDS[book] for book in p.books]))


play_go_fish(['Patrik', 'Eva', "Moa", "Elin"], 2)
