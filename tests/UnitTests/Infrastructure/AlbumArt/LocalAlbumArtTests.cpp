#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <Mocks/AlbumArtDownloaderMock.hpp>
#include <Mocks/StreamingServiceLoaderMock.hpp>
#include <Mocks/StreamingServiceWatcherMock.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("LocalAlbumArtTests", "[UnitTest]")
{
    auto serviceLoaderMock = StreamingServiceLoaderMock::get();
    auto watcherMock = StreamingServiceWatcherMock::get();
    StreamingServices streamingServices(serviceLoaderMock.get(), watcherMock.get());
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    AlbumArtDownloaderMock albumArtDownloader;
    QSignalSpy downloadFinishedSpy(&albumArtDownloader, SIGNAL(downloadFinished(const QString&)));
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);

    SECTION("download when current song changed")
    {
        QString url = "https://deezer.com/arUrl-123.png";
        QString songId = "songId";

        Song song(songId, "", "", "", url, 0, false);
        emit player.currentSongChanged(&song);
        REQUIRE(downloadFinishedSpy.count() == 1);
        REQUIRE(downloadFinishedSpy[0][0] == LOCAL_URL);
        REQUIRE(localAlbumArt.url() == LOCAL_URL);
        REQUIRE(!localAlbumArt.isSongArtReady(song)); // file does not exist because we use a downloader mock
    }
}
